/*class TestGenInfoProduct
 *  
 *  Class to dump Run and Event GEN level InfoProduct
 *
 *  $Date: 2012/10/05 12:51:52 $
 *  $Revision: 1.1 $
 */
 
#include "TestGenInfoProduct.h"

#include "CLHEP/Units/defs.h"
#include "CLHEP/Units/PhysicalConstants.h"

using namespace edm;

TestGenInfoProduct::TestGenInfoProduct(const edm::ParameterSet& iPSet):  
  genrunCollection_(iPSet.getParameter<edm::InputTag>("genrunCollection")),
  genevtCollection_(iPSet.getParameter<edm::InputTag>("genevtCollection"))
{    
}

TestGenInfoProduct::~TestGenInfoProduct() {}

void TestGenInfoProduct::beginJob()
{
}

void TestGenInfoProduct::endJob(){return;}
void TestGenInfoProduct::beginRun(const edm::Run& iRun,const edm::EventSetup& iSetup)
{

  // Gather information on the GenRunInfoProduct collection
  edm::Handle<GenRunInfoProduct> genrun;
  iRun.getByLabel(genrunCollection_, genrun );

  std::cout << "Internal cross section     = " << std::setw(14) << std::fixed << genrun->internalXSec().value() << " +- " 
            << std::setw(14) << std::fixed << genrun->internalXSec().error() << " isSet = " << genrun->internalXSec().isSet() << std::endl;
  std::cout << "External LO cross section  = " << std::setw(14) << std::fixed << genrun->externalXSecLO().value() << " +- " 
            << std::setw(14) << std::fixed << genrun->externalXSecLO().error() << " isSet = " << genrun->externalXSecLO().isSet() << std::endl;
  std::cout << "External NLO cross section = " << std::setw(14) << std::fixed << genrun->externalXSecNLO().value() << " +- "
            << std::setw(14) << std::fixed << genrun->externalXSecNLO().error() << " isSet = " << genrun->externalXSecNLO().isSet() << std::endl;
  std::cout << "Filter efficiency          = " << std::setw(14) << std::fixed << genrun->filterEfficiency() << std::endl;

  return;
}
void TestGenInfoProduct::endRun(const edm::Run& iRun,const edm::EventSetup& iSetup){return;}
void TestGenInfoProduct::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup)
{ 

  // Gather information on the GenEventInfoProduct collection

  edm::Handle<GenEventInfoProduct> genevt;
  iEvent.getByLabel(genevtCollection_, genevt );

  std::cout << "Signal process ID = " << std::setw(14) << std::fixed << genevt->signalProcessID() 
            << " Scale = " << std::setw(14) << std::fixed << genevt->qScale() 
            << " Alpha_QCD = " << std::setw(14) << std::fixed << genevt->alphaQCD() 
            << " Alpha_QED = " << std::setw(14) << std::fixed << genevt->alphaQED() 
            << " Global weight = " << std::setw(14) << std::fixed << genevt->weight() << std::endl;

  for ( unsigned int iw = 0 ; iw < genevt->weights().size() ; iw++ ) {
    std::cout << "Weight " << std::setw(3) << std::fixed << iw << " = " << std::setw(14) << std::fixed << genevt->weights()[iw] << std::endl;
  }

  if ( genevt->hasBinningValues() ) {
    for ( unsigned int iw = 0 ; iw < genevt->binningValues().size() ; iw++ ) {
      std::cout << "Bin " << std::setw(3) << std::fixed << iw << " = " << std::setw(14) << std::fixed << genevt->binningValues()[iw] << std::endl;
    }
  }

  if ( genevt->hasPDF() ) {
    std::cout << "PDF scale = " << std::setw(14) << std::fixed << genevt->pdf()->scalePDF << std::endl;  
    std::cout << "PDF 1 : id = " << std::setw(14) << std::fixed << genevt->pdf()->id.first 
              << " x = " << std::setw(14) << std::fixed << genevt->pdf()->x.first 
              << " xPDF = " << std::setw(14) << std::fixed << genevt->pdf()->xPDF.first << std::endl;  
    std::cout << "PDF 2 : id = " << std::setw(14) << std::fixed << genevt->pdf()->id.second 
              << " x = " << std::setw(14) << std::fixed << genevt->pdf()->x.second 
              << " xPDF = " << std::setw(14) << std::fixed << genevt->pdf()->xPDF.second << std::endl;  
  }

}//analyze

