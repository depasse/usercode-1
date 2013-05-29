#ifndef TESTPDF_H
#define TESTPDF_H

/*class TestPDF
 *  
 *  Class to study Reco Vertices
 *
 *  $Date: 2012/08/29 14:31:22 $
 *  $Revision: 1.2 $
 *
 */

// framework & common header files
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "TH1F.h"

class TestPDF : public edm::EDAnalyzer
{
    public:
	explicit TestPDF(const edm::ParameterSet&);
	virtual ~TestPDF();
	virtual void beginJob();
	virtual void endJob();  
	virtual void analyze(const edm::Event&, const edm::EventSetup&);
	virtual void beginRun(const edm::Run&, const edm::EventSetup&);
	virtual void endRun(const edm::Run&, const edm::EventSetup&);

    private:

    edm::InputTag genCollection_;

    std::string pdfWeightProd_;
    std::string pdfSetName_;
    std::string pdfShortName_;

    TH1F* x1OrigHisto_;
    TH1F* x2OrigHisto_;
    TH1F* x1x2OrigHisto_;
    TH1F* x1x2WeiHisto_;
    TH1F* weightHisto_;

    double x1;
    double x2;

};

#endif
