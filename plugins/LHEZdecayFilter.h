#ifndef LHEZDECAYFILTER_h
#define LHEZDECAYFILTER_h
// -*- C++ -*-
//
// Package:    LHEZdecayFilter
// Class:      LHEZdecayFilter
// 
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


//
// class decleration
//

class LHEZdecayFilter : public edm::EDFilter {
   public:
      explicit LHEZdecayFilter(const edm::ParameterSet&);
      ~LHEZdecayFilter();


      virtual bool filter(edm::Event&, const edm::EventSetup&);
   private:
      // ----------member data ---------------------------
      
      edm::InputTag src_;
      int leptonID_;
      bool verbose_;
};
#endif
