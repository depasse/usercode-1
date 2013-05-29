// -*- C++ -*-
//
// Package:    TrackTest
// Class:      TrackTest
// 
/**\class TrackTest TrackTest.cc Test/TrackTest/src/TrackTest.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Giuseppe Cerati,28 S-012,+41227678302,
//         Created:  Thu Dec 13 12:06:32 CET 2012
// $Id: TrackTest.cc,v 1.3 2013/01/30 17:37:09 fabiocos Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "TrackingTools/Records/interface/TransientRecHitRecord.h"
#include "TrackingTools/TransientTrackingRecHit/interface/TransientTrackingRecHitBuilder.h"
#include "DataFormats/SiStripDetId/interface/TIBDetId.h"
#include "DataFormats/SiStripDetId/interface/TOBDetId.h"
#include "DataFormats/SiStripDetId/interface/TIDDetId.h"
#include "DataFormats/SiStripDetId/interface/TECDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXBDetId.h"
#include "DataFormats/SiPixelDetId/interface/PXFDetId.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1F.h"

//
// class declaration
//

class TrackTest : public edm::EDAnalyzer {
public:
  explicit TrackTest(const edm::ParameterSet&);
  ~TrackTest();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  // ----------member data ---------------------------
  edm::InputTag trackTags_; //used to select what tracks to read from configuration file
  std::string builderName;
  const TransientTrackingRecHitBuilder* builder;

  TH1F * hpntrkHisto_;
  TH1F * hpnchaHisto_;
  TH1F * pttrkHisto_;
  TH1F * ptplusHisto_;
  TH1F * ptminusHisto_;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TrackTest::TrackTest(const edm::ParameterSet& iConfig)
  :
  trackTags_(iConfig.getUntrackedParameter<edm::InputTag>("tracks")),
  builderName(iConfig.getParameter<std::string>("TTRHBuilder"))

{
  //now do what ever initialization is needed
  edm::Service<TFileService> fs;

  hpntrkHisto_ = fs->make<TH1F>( "hpntrk", "high purity track multiplicity", 100, 0., 100. ) ;
  hpnchaHisto_ = fs->make<TH1F>( "hpncha", "high purity track charge", 3, -1., 2. ) ;
  pttrkHisto_ = fs->make<TH1F>( "pttrk", "high purity track pt", 1000, 0., 100. ) ;
  ptplusHisto_ = fs->make<TH1F>( "ptplus", "high purity positive track pt", 1000, 0., 100. ) ;
  ptminusHisto_ = fs->make<TH1F>( "ptminus", "high purity negative track pt", 1000, 0., 100. ) ;

}


TrackTest::~TrackTest()
{
 
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TrackTest::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;

  using reco::TrackCollection;

  Handle<TrackCollection> tracks;
  iEvent.getByLabel(trackTags_,tracks);
  int ntrk = 0 ;
  int hpntrk = 0 ;
  for(TrackCollection::const_iterator itTrack = tracks->begin(); itTrack != tracks->end(); ++itTrack) {

    edm::LogInfo("TrackInfo") << "Track #" << ntrk << " with q=" << itTrack->charge() 
                              << ", pT=" << itTrack->pt() << " GeV, eta=" << itTrack->eta() 
                              << ", Nhits=" << itTrack->recHitsSize() 
                              << ", algo=" << itTrack->algoName(itTrack->algo()).c_str() 
                              << ", hp quality=" << itTrack->quality(reco::Track::highPurity);


    if ( itTrack->quality(reco::Track::highPurity) ) {
      hpntrk++;
      hpnchaHisto_->Fill(itTrack->charge());
      pttrkHisto_->Fill(itTrack->pt());
      if ( itTrack->charge() > 0. ) { ptplusHisto_->Fill(itTrack->pt()); }
      else if ( itTrack->charge() < 0. ) { ptminusHisto_->Fill(itTrack->pt()); }
    }

    int nhit = 0;
    for (trackingRecHit_iterator i=itTrack->recHitsBegin(); i!=itTrack->recHitsEnd(); i++){
      edm::LogInfo("HitInfo") << "hit #" << nhit;
      TransientTrackingRecHit::RecHitPointer hit=builder->build(&**i );
      DetId hitId = hit->geographicalId();
      if(hitId.det() == DetId::Tracker) {
        if (hitId.subdetId() == StripSubdetector::TIB )  
          edm::LogInfo("HitInfo") << " - TIB " << TIBDetId(hitId).layer();
        else if (hitId.subdetId() == StripSubdetector::TOB ) 
          edm::LogInfo("HitInfo") << " - TOB " << TOBDetId(hitId).layer();
        else if (hitId.subdetId() == StripSubdetector::TEC ) 
          edm::LogInfo("HitInfo") << " - TEC " << TECDetId(hitId).wheel();
        else if (hitId.subdetId() == StripSubdetector::TID ) 
          edm::LogInfo("HitInfo") << " - TID " << TIDDetId(hitId).wheel();
        else if (hitId.subdetId() == StripSubdetector::TID ) 
          edm::LogInfo("HitInfo") << " - TID " << TIDDetId(hitId).wheel();
        else if (hitId.subdetId() == (int) PixelSubdetector::PixelBarrel ) 
          edm::LogInfo("HitInfo") << " - PixBar " << PXBDetId(hitId).layer();
        else if (hitId.subdetId() == (int) PixelSubdetector::PixelEndcap )
          edm::LogInfo("HitInfo") << " - PixFwd " << PXFDetId(hitId).disk();
        else 
          edm::LogInfo("HitInfo") << " UNKNOWN TRACKER HIT TYPE ";
      }
      if (hit->isValid()) edm::LogInfo("HitInfo") << " - globalPos =" << hit->globalPosition() << endl;
      else edm::LogInfo("HitInfo") << " - invalid hit";
      nhit++;
    }

    ntrk++;

  }

  hpntrkHisto_->Fill((float)hpntrk);

}


// ------------ method called once each job just before starting event loop  ------------
void 
TrackTest::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TrackTest::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
TrackTest::beginRun(edm::Run const& run, edm::EventSetup const& setup)
{

  edm::ESHandle<TransientTrackingRecHitBuilder> theBuilder;
  setup.get<TransientRecHitRecord>().get(builderName,theBuilder);
  builder=theBuilder.product();
}

// ------------ method called when ending the processing of a run  ------------
void 
TrackTest::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
TrackTest::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
TrackTest::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TrackTest::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TrackTest);
