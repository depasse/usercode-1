/*class MonitorPUSummaryInfo
 *  
 *  Class to study Reco Vertices
 *
 *  $Date: 2013/02/02 22:10:28 $
 *  $Revision: 1.4 $
 */
 
#include "MonitorPUSummaryInfo.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

using namespace edm;

MonitorPUSummaryInfo::MonitorPUSummaryInfo(const edm::ParameterSet& iPSet):  
  puSummaryCollection_(iPSet.getParameter<edm::InputTag>("puSummaryCollection"))
{    

  edm::Service<TFileService> fs;

  nBXHisto_ = fs->make<TH1F>( "nBX", "n. bunch crossings", 20, -10., 10. ) ;
  nPUHisto_ = fs->make<TH1F>( "nPU", "n PU events", 200, 0., 200. ) ;
  nTruePUHisto_ = fs->make<TH1F>( "nTruePU", "n true PU events", 200, 0., 200. ) ;
  zPUHisto_ = fs->make<TH1F>( "zPU", "z PU events", 400, -20., 20. ) ;
  nPUvsBXHisto_ = fs->make<TProfile>( "nPUvsBX", "n PU events vs BX", 20, -10., 10., 0., 200. ) ;
  nTruePUvsBXHisto_ = fs->make<TProfile>( "nTruePUvsBX", "n true PU events vs BX", 20, -10., 10., 0., 200. ) ;

  nTruem1Histo_ = fs->make<TH1F>( "nTruem1", "n true PU events BX -1", 200, 0., 200. ) ;
  nTrue0Histo_ = fs->make<TH1F>( "nTrue0", "n true PU events BX 0", 200, 0., 200. ) ;
  nTruep1Histo_ = fs->make<TH1F>( "nTruep1", "n true PU events BX 1", 200, 0., 200. ) ;
  nPUm1Histo_ = fs->make<TH1F>( "nPUm1", "n PU events BX -1", 200, 0., 200. ) ;
  nPU0Histo_ = fs->make<TH1F>( "nPU0", "n PU events BX 0", 200, 0., 200. ) ;
  nPUp1Histo_ = fs->make<TH1F>( "nPUp1", "n PU events BX 1", 200, 0., 200. ) ;

  nPUvsTruePUHisto_ = fs->make<TH2F>( "nPUvsTruePU", "n PU vs True PU", 200, 0., 200., 200, 0., 200. ) ;

}

MonitorPUSummaryInfo::~MonitorPUSummaryInfo() {}

void MonitorPUSummaryInfo::beginJob()
{
}

void MonitorPUSummaryInfo::endJob(){return;}
void MonitorPUSummaryInfo::beginRun(const edm::Run& iRun,const edm::EventSetup& iSetup)
{
}
void MonitorPUSummaryInfo::endRun(const edm::Run& iRun,const edm::EventSetup& iSetup){return;}
void MonitorPUSummaryInfo::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup)
{ 

  edm::Handle<std::vector< PileupSummaryInfo> > puSummary;
  iEvent.getByLabel(puSummaryCollection_, puSummary );

  for ( unsigned int ibx = 0 ; ibx < (*puSummary).size(); ibx++ ) {

    nBXHisto_->Fill((float)(*puSummary)[ibx].getBunchCrossing());
    nPUHisto_->Fill((float)(*puSummary)[ibx].getPU_NumInteractions());
    nTruePUHisto_->Fill((*puSummary)[ibx].getTrueNumInteractions());
    nPUvsBXHisto_->Fill((float)(*puSummary)[ibx].getBunchCrossing(),(float)(*puSummary)[ibx].getPU_NumInteractions());
    nTruePUvsBXHisto_->Fill((float)(*puSummary)[ibx].getBunchCrossing(),(*puSummary)[ibx].getTrueNumInteractions());

    nPUvsTruePUHisto_->Fill((*puSummary)[ibx].getTrueNumInteractions(),(float)(*puSummary)[ibx].getPU_NumInteractions()); 

    
    edm::LogInfo("PUSummaryInfo") << "\n # BX      = " << (*puSummary)[ibx].getBunchCrossing() 
                                  << "\n # PU      = " << (*puSummary)[ibx].getPU_NumInteractions() 
                                  << "\n # true PU = " << (*puSummary)[ibx].getTrueNumInteractions() ;
    
    for ( unsigned int ivtx = 0; ivtx < (*puSummary)[ibx].getPU_zpositions().size(); ivtx++ ) {
      zPUHisto_->Fill((*puSummary)[ibx].getPU_zpositions()[ivtx]); 
    }

    if ( (*puSummary)[ibx].getBunchCrossing() == -1 ) {
      nPUm1Histo_->Fill((float)(*puSummary)[ibx].getPU_NumInteractions());
      nTruem1Histo_->Fill((*puSummary)[ibx].getTrueNumInteractions());
    }
    else if ( (*puSummary)[ibx].getBunchCrossing() == 0 ) {  
      nPU0Histo_->Fill((float)(*puSummary)[ibx].getPU_NumInteractions());
      nTrue0Histo_->Fill((*puSummary)[ibx].getTrueNumInteractions());
    }
    else if ( (*puSummary)[ibx].getBunchCrossing() == 1 ) {  
      nPUp1Histo_->Fill((float)(*puSummary)[ibx].getPU_NumInteractions());
      nTruep1Histo_->Fill((*puSummary)[ibx].getTrueNumInteractions());
    }
    
  }

}//analyze

