#ifndef MONITORCROSSINGFRAMEPLAYBACKEXTENDEDINFO_H
#define MONITORCROSSINGFRAMEPLAYBACKEXTENDEDINFO_H

/*class MonitorPUSummaryInfo
 *  
 *  Class to study Reco Vertices
 *
 *  $Date: 2012/11/21 14:45:50 $
 *  $Revision: 1.1 $
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

#include "SimDataFormats/CrossingFrame/interface/CrossingFramePlaybackInfoExtended.h"

class MonitorCrossingFramePlaybackInfoExtended : public edm::EDAnalyzer
{
    public:
	explicit MonitorCrossingFramePlaybackInfoExtended(const edm::ParameterSet&);
	virtual ~MonitorCrossingFramePlaybackInfoExtended();
	virtual void beginJob();
	virtual void endJob();  
	virtual void analyze(const edm::Event&, const edm::EventSetup&);
	virtual void beginRun(const edm::Run&, const edm::EventSetup&);
	virtual void endRun(const edm::Run&, const edm::EventSetup&);

    private:

    edm::InputTag puSummaryCollection_;

    unsigned int nSource;
    unsigned int nBX;
    int minBunch;

};

#endif
