
#include <iostream>

#include "SimPVMonitor.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "HepMC/GenRanges.h"

using namespace edm;
using namespace std;

SimPVMonitor::SimPVMonitor( const ParameterSet& iPSet ):
  src_(iPSet.getParameter<edm::InputTag>("src"))
{

  edm::Service<TFileService> fs;
  fVtxHistz      = fs->make<TH1F>("VtxHistz","Test Z-spread", 100, -250., 250. ) ;
  fVtxHistx      = fs->make<TH1F>("VtxHistx","Test X-spread", 200, -10., 10. ) ;
  fVtxHisty      = fs->make<TH1F>("VtxHisty","Test Y-spread", 200, -10., 10. ) ;
  fVtxHistxy     = fs->make<TH2F>("VtxHistxy","Test X-Y spread",200,-10.,10.,200,-10.,10.);
  
}

void SimPVMonitor::beginJob()
{
}

void SimPVMonitor::endJob(){return;}

void SimPVMonitor::analyze( const Event& e, const EventSetup& )
{
   
  edm::Handle<edm::HepMCProduct> HepMCEvt ;
  
  e.getByLabel( src_ , HepMCEvt ) ;  

  HepMC::GenEvent::vertex_const_iterator vitr= HepMCEvt->GetEvent()->vertex_range().begin();
  
  if ( vitr != HepMCEvt->GetEvent()->vertex_range().end() ) { 

    fVtxHistz->Fill( (float)(*vitr)->position().z() ) ;
    fVtxHistx->Fill( (float)(*vitr)->position().x() ) ;
    fVtxHisty->Fill( (float)(*vitr)->position().y() ) ;
    fVtxHistxy->Fill( (float)(*vitr)->position().x(),(float)(*vitr)->position().y() );
    
  }
  
  return ;
}
