#ifndef SimPVMonitor_H
#define SimPVMonitor_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TH1F.h"
#include "TH2F.h"

class SimPVMonitor : public edm::EDAnalyzer
{
  
 public:
  
  //
  explicit SimPVMonitor( const edm::ParameterSet& ) ;
  virtual ~SimPVMonitor() {}
  
  virtual void analyze( const edm::Event&, const edm::EventSetup& ) ;
  virtual void beginJob();
  virtual void endJob();  
  
 private:

  edm::InputTag src_;
  
  TH1F*  fVtxHistz ;
  TH1F*  fVtxHistx ;
  TH1F*  fVtxHisty ;
  TH2F* fVtxHistxy;
  
};

#endif
