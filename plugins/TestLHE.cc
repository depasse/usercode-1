#include "TestLHE.h"

TestLHE::TestLHE( const edm::ParameterSet & cfg ) : 
  src_( cfg.getParameter<edm::InputTag>( "src" ) )
  {
    nE = 0;
    nM = 0;
    nT = 0;
  }

void TestLHE::analyze( const edm::Event & iEvent, const edm::EventSetup & iSetup ) {

  edm::Handle<LHEEventProduct> evt;
  iEvent.getByLabel( src_, evt );

  const lhef::HEPEUP hepeup_ = evt->hepeup();
  
  const int nup_ = hepeup_.NUP; 
  const std::vector<int> idup_ = hepeup_.IDUP;
  const std::vector<lhef::HEPEUP::FiveVector> pup_ = hepeup_.PUP;
  
  std::cout << "Number of particles = " << nup_ << std::endl;
  
  for ( unsigned int icount = 0 ; icount < (unsigned int)nup_; icount++ ) {
    
    std::cout << "# " << icount << " " << idup_[icount] << " " << (pup_[icount])[0] << " " << (pup_[icount])[1] << " " << (pup_[icount])[2] << " " << (pup_[icount])[3] << " " << (pup_[icount])[4] << std::endl;
    
    if ( std::abs(idup_[icount]) == 11 ) { nE++; break; }
    else if ( std::abs(idup_[icount]) == 13 ) { nM++; break; }
    else if ( std::abs(idup_[icount]) == 15 ) { nT++; break; }
    
    std::cout << "# E/M/T = " << nE << " " << nM << " " << nT << std::endl;
    
  }
  
  
}

void TestLHE::endJob(){
  
  std::cout << "# Electron = " << nE << std::endl;
  std::cout << "# Muon     = " << nM << std::endl;
  std::cout << "# Tau      = " << nT << std::endl;
  
}


