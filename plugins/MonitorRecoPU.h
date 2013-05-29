#ifndef MONITORRECOPU_H
#define MONITORRECOPU_H

/*class MonitorRecoPU
 *  
 *  Class to study Reco Vertices
 *
 *  $Date: 2011/12/15 16:08:18 $
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

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"

#include "TH1F.h"

class MonitorRecoPU : public edm::EDAnalyzer
{
    public:
	explicit MonitorRecoPU(const edm::ParameterSet&);
	virtual ~MonitorRecoPU();
	virtual void beginJob();
	virtual void endJob();  
	virtual void analyze(const edm::Event&, const edm::EventSetup&);
	virtual void beginRun(const edm::Run&, const edm::EventSetup&);
	virtual void endRun(const edm::Run&, const edm::EventSetup&);

    private:

    edm::InputTag recoVertexCollection_;
    edm::InputTag pixelClusterCollection_;

    TH1F * vtxHisto_;
    TH1F * pixcluHisto_;

};

#endif
