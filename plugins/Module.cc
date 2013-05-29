#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "LHEZdecayFilter.h"
DEFINE_FWK_MODULE (LHEZdecayFilter);

#include "TestLHE.h"
DEFINE_FWK_MODULE (TestLHE);

#include "TestGenParticle.h"
DEFINE_FWK_MODULE (TestGenParticle);

#include "TestHepMC.h"
DEFINE_FWK_MODULE (TestHepMC);

#include "TestRecoVertex.h"
DEFINE_FWK_MODULE (TestRecoVertex);

#include "MonitorRecoPU.h"
DEFINE_FWK_MODULE (MonitorRecoPU);

#include "MonitorPUSummaryInfo.h"
DEFINE_FWK_MODULE (MonitorPUSummaryInfo);

#include "MonitorCrossingFramePlaybackInfoExtended.h"
DEFINE_FWK_MODULE (MonitorCrossingFramePlaybackInfoExtended);

#include "SimPVMonitor.h"
DEFINE_FWK_MODULE (SimPVMonitor);

#include "TestPDF.h"
DEFINE_FWK_MODULE (TestPDF);

#include "TestGenInfoProduct.h"
DEFINE_FWK_MODULE (TestGenInfoProduct);

#include "MonitorMixCollection.h"
DEFINE_FWK_MODULE (MonitorMixCollection); 
