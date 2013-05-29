/*class MonitorCrossingFramePlaybackInfoExtended
 *  
 *  Class to study Reco Vertices
 *
 *  $Date: 2012/11/21 14:45:50 $
 *  $Revision: 1.1 $
 */
 
#include "MonitorCrossingFramePlaybackInfoExtended.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

using namespace edm;

MonitorCrossingFramePlaybackInfoExtended::MonitorCrossingFramePlaybackInfoExtended(const edm::ParameterSet& iPSet):  
  puSummaryCollection_(iPSet.getParameter<edm::InputTag>("puSummaryCollection")),
  nSource(iPSet.getParameter<uint32_t>("nSource")),
  nBX(iPSet.getParameter<uint32_t>("nBX")),
  minBunch(iPSet.getParameter<int32_t>("minBunch"))
{    
}

MonitorCrossingFramePlaybackInfoExtended::~MonitorCrossingFramePlaybackInfoExtended() {}

void MonitorCrossingFramePlaybackInfoExtended::beginJob()
{
}

void MonitorCrossingFramePlaybackInfoExtended::endJob(){return;}
void MonitorCrossingFramePlaybackInfoExtended::beginRun(const edm::Run& iRun,const edm::EventSetup& iSetup)
{
}
void MonitorCrossingFramePlaybackInfoExtended::endRun(const edm::Run& iRun,const edm::EventSetup& iSetup){return;}
void MonitorCrossingFramePlaybackInfoExtended::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup)
{ 

  edm::Handle<CrossingFramePlaybackInfoExtended> puSummary;
  iEvent.getByLabel(puSummaryCollection_, puSummary );

  for ( unsigned int iS = 0; iS < nSource ; iS++ ) {
  
    for ( int iB = minBunch ; iB < (int)(minBunch+nBX) ; iB++ ){
  
      std::vector<edm::EventID> thePU = puSummary->getStartEventId(iS, iB);
      for ( unsigned int iEv = 0; iEv < thePU.size() ; iEv++ ) {
        std::cout << iEv+1 << " Source # = " << iS << " BX # = " << iB << " " << thePU[iEv] << std::endl;
      }
    }
    
  }

}//analyze

