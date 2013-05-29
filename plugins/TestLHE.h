#ifndef TESTLHE_H
#define TESTLHE_H

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include <iostream>

class TestLHE : public edm::EDAnalyzer {
  
 public:
  explicit TestLHE( const edm::ParameterSet & cfg ); 
  
 private:
  
  edm::InputTag src_;
  int nE, nM, nT;
  
  void analyze( const edm::Event & iEvent, const edm::EventSetup & iSetup ) ;
  
  void endJob();
  
};

#endif


