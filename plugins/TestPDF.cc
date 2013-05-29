/*class TestPDF
 *  
 *  Class to study Reco Vertices
 *
 *  $Date: 2012/09/03 20:27:43 $
 *  $Revision: 1.3 $
 */
 
#include "TestPDF.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "CLHEP/Units/defs.h"
#include "CLHEP/Units/PhysicalConstants.h"

using namespace edm;

TestPDF::TestPDF(const edm::ParameterSet& iPSet):  
  genCollection_(iPSet.getParameter<edm::InputTag>("genCollection")),
  pdfWeightProd_(iPSet.getParameter<std::string> ("PdfWeightProd")),
  pdfSetName_(iPSet.getParameter<std::string>  ("PdfSetName"))
{    

  edm::Service<TFileService> fs;

  x1OrigHisto_ = fs->make<TH1F>( "x1", "x1", 100, 0., 1. );
  x2OrigHisto_ = fs->make<TH1F>( "x2", "x2", 100, 0., 1. );

  x1x2OrigHisto_ = fs->make<TH1F>( "sqrt(x1x2) Orig", "sqrt(x1x2)", 100, 0., 1. );
  x1x2WeiHisto_ = fs->make<TH1F>( "sqrt(x1x2) Weight", "sqrt(x1x2)", 100, 0., 1. );
  weightHisto_ = fs->make<TH1F>( "Weight", "Weight", 100, -0.5, 1.5 );

}

TestPDF::~TestPDF() {}

void TestPDF::beginJob()
{
}

void TestPDF::endJob(){return;}
void TestPDF::beginRun(const edm::Run& iRun,const edm::EventSetup& iSetup)
{
 return;
}
void TestPDF::endRun(const edm::Run& iRun,const edm::EventSetup& iSetup){return;}
void TestPDF::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup)
{ 

  ///Gathering the GenEventInfoProduct information
  edm::Handle<GenEventInfoProduct> evt;
  iEvent.getByLabel(genCollection_, evt);

  x1 = evt->pdf()->x.first;
  x2 = evt->pdf()->x.second;

  x1OrigHisto_->Fill(sqrt(x1));
  x2OrigHisto_->Fill(sqrt(x2));
  x1x2OrigHisto_->Fill(sqrt(x1*x2));

  size_t dot = pdfSetName_.find_first_of('.');
  size_t underscore = pdfSetName_.find_first_of('_');
  if (underscore<dot) {
    pdfShortName_ = pdfSetName_.substr(0,underscore);
  } else {
    pdfShortName_ = pdfSetName_.substr(0,dot);
  }

  edm::Handle<std::vector<double>> stuff;
  iEvent.getByLabel(pdfWeightProd_ , pdfShortName_ , stuff);
  double weight = stuff->at(0);
  weightHisto_->Fill(weight);
  x1x2WeiHisto_->Fill(sqrt( x1 * x2 ) , weight );
       
  edm::LogInfo("TestPDFInfo") << "Reweight to PDF " << pdfShortName_ 
                              << " x1 = " << x1 << " x2 = " << x2
                              << " sqrt(x1*x2) = " << sqrt(x1*x2) 
                              << " weight = " << weight;

}//analyze


