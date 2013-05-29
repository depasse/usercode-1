/*class EcalMinBiasAnalysis
 *  
 *  Class to study ECAL response in Minimum Bias events
 *
 *  $Date: 2013/03/14 10:35:54 $
 *  $Revision: 1.15 $
 *
 */

// framework & common header files
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"

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

#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

#include "DataFormats/EcalDigi/interface/EEDataFrame.h"
#include "DataFormats/EcalDigi/interface/EcalMGPASample.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "CondFormats/EcalObjects/interface/EcalChannelStatus.h"
#include "CondFormats/DataRecord/interface/EcalChannelStatusRcd.h"
#include "CondFormats/EcalObjects/interface/EcalPedestals.h"
#include "CondFormats/DataRecord/interface/EcalPedestalsRcd.h"

#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


#include "CLHEP/Vector/ThreeVector.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"

class EcalMinBiasAnalysis : public edm::EDAnalyzer
{

public:
  explicit EcalMinBiasAnalysis(const edm::ParameterSet&);
  virtual ~EcalMinBiasAnalysis();
  virtual void beginJob();
  virtual void endJob();  
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void beginRun(const edm::Run&, const edm::EventSetup&);
  virtual void endRun(const edm::Run&, const edm::EventSetup&);
  
private:
  
  edm::InputTag recoVertexCollection_;
  edm::InputTag pixelClusterCollection_;
  edm::InputTag ebRecHitCollection_; 
  edm::InputTag eeRecHitCollection_; 
  edm::InputTag eeDigiCollection_; 

  int vtxSel_;
  
  TH1F * vtxHisto_;
  TH1F * pixcluHisto_;
  TH1F * ebmultiHisto_;
  TH1F * eemultiHisto_;
  TH1F * eehitEneAllHisto_;
  TH1F * eehit1EtaHisto_;
  TH1F * eehit1EneHisto_;
  TH1F * eehit1ETHisto_;
  TH1F * eehit1SumETHisto_;
  TH1F * eehit1TimeHisto_;
  TH1F * eehit1Chi2Histo_;
  TH1F * eehit5EtaHisto_;
  TH1F * eehit5EneHisto_;
  TH1F * eehit5ETHisto_;
  TH1F * eehit5SumETHisto_;
  TH1F * eehit5TimeHisto_;
  TH1F * eehit5Chi2Histo_;

  TH1F * eehit15SumETHisto_;

  TH2F * ee1TimeVSEneHisto_;
  TH2F * ee5TimeVSEneHisto_;

  std::vector<TH1F*> ee1DigiADC_;
  std::vector<TH1F*> ee1DigiGain_;
  TProfile* ee1FrameProfile_; 
  TProfile* ee1FrameProfileNoPed_; 

  std::vector<TH1F*> ee5DigiADC_;
  std::vector<TH1F*> ee5DigiGain_;
  TProfile* ee5FrameProfile_; 
  TProfile* ee5FrameProfileNoPed_; 

  std::vector<TH1F*> ee1SumETvtxHisto_;
  std::vector<TH1F*> ee5SumETvtxHisto_;

  TProfile* ee1SumEVSeta_;
  TProfile* ee5SumEVSeta_;
  TProfile* ee1SumETVSeta_;
  TProfile* ee5SumETVSeta_;

  TProfile* ee1SumETVSvtx_;
  TProfile* ee5SumETVSvtx_;

  const float lowEta;
  const float highEta;
  const int nEta;
  const int numvtx;

};

using namespace edm;

EcalMinBiasAnalysis::EcalMinBiasAnalysis(const edm::ParameterSet& iPSet):  
  recoVertexCollection_(iPSet.getParameter<edm::InputTag>("recoVertexCollection")),
  pixelClusterCollection_(iPSet.getParameter<edm::InputTag>("pixelClusterCollection")),
  ebRecHitCollection_(iPSet.getParameter<edm::InputTag>("ebRecHitCollection")),
  eeRecHitCollection_(iPSet.getParameter<edm::InputTag>("eeRecHitCollection")),
  eeDigiCollection_(iPSet.getParameter<edm::InputTag>("eeDigiCollection")),
  vtxSel_(iPSet.getParameter<int>("vtxSel")),lowEta(1.4),highEta(3.),nEta(80),numvtx(60)
{    

  edm::Service<TFileService> fs;

  vtxHisto_ = fs->make<TH1F>( "vtx", "vertex ndof.gt.4 multiplicity", 100, 0., 100. ) ;
  pixcluHisto_ = fs->make<TH1F>( "pixclu", "pixel cluster multiplicity", 100, 0., 2000. ) ;
  ebmultiHisto_ = fs->make<TH1F>( "ebmulti", "EB hits multiplicity", 60, 0., 3000. ); 
  eemultiHisto_ = fs->make<TH1F>( "eemulti", "EE hits multiplicity", 60, 0., 3000. ); 
  eehitEneAllHisto_ = fs->make<TH1F>( "eehitEneAll", "EE all hits energy", 1000, 0., 100. ); 
  eehit1EtaHisto_ = fs->make<TH1F>( "eehit1Eta", "EE hits abs eta .gt. 0.1", nEta, lowEta, highEta ); 
  eehit1EneHisto_ = fs->make<TH1F>( "eehit1Ene", "EE hits energy .gt. 0.1", 1000, 0., 100. ); 
  eehit1ETHisto_ = fs->make<TH1F>( "eehit1ET", "EE hits e_T .gt. 0.1", 500, 0., 50. ); 
  eehit1SumETHisto_ = fs->make<TH1F>( "eehit1SumET", "EE hits sum e_T .gt. 0.1", 500, 0., 500. ); 
  eehit1TimeHisto_ = fs->make<TH1F>( "eehit1Time", "EE hits time .gt. 0.1", 200, -100., 100. ); 
  eehit1Chi2Histo_ = fs->make<TH1F>( "eehit1Chi2", "EE hits chi2 .gt. 0.1", 100, 0., 100. ); 
  eehit5EtaHisto_ = fs->make<TH1F>( "eehit5Eta", "EE hits abs eta .gt. 0.5", nEta, lowEta, highEta ); 
  eehit5EneHisto_ = fs->make<TH1F>( "eehit5Ene", "EE hits energy .gt. 0.5", 1000, 0., 100. ); 
  eehit5ETHisto_ = fs->make<TH1F>( "eehit5ET", "EE hits e_T .gt. 0.5", 500, 0., 50. ); 
  eehit5SumETHisto_ = fs->make<TH1F>( "eehit5SumET", "EE hits sum e_T .gt. 0.5", 500, 0., 500. ); 
  eehit5TimeHisto_ = fs->make<TH1F>( "eehit5Time", "EE hits time .gt. 0.5", 200, -100., 100. ); 
  eehit5Chi2Histo_ = fs->make<TH1F>( "eehit5Chi2", "EE hits chi2 .gt. 0.5", 100, 0., 100. ); 

  eehit15SumETHisto_ = fs->make<TH1F>( "eehit15SumET", "EE hits sum e_T 0.1 .le. 0.5", 500, 0., 500.);  

  ee1TimeVSEneHisto_ = fs->make<TH2F>( "ee1TimeVSEne", "EE hits .gt. 0.1 Time VS Ene", 50, 0., 100., 100, -100., 100. ); 
  ee5TimeVSEneHisto_ = fs->make<TH2F>( "ee5TimeVSEne", "EE hits .gt. 0.5 Time VS Ene", 50, 0., 100., 100, -100., 100. ); 

  ee1SumEVSeta_ = fs->make<TProfile>( "ee1SumEVSeta", "EE hits .gt. 0.1 SumE VS Eta", nEta, lowEta, highEta, 0., 500.); 
  ee1SumETVSeta_ = fs->make<TProfile>( "ee1SumETVSeta", "EE hits .gt. 0.1 SumET VS Eta", nEta, lowEta, highEta, 0., 500.); 
  ee5SumEVSeta_ = fs->make<TProfile>( "ee5SumEVSeta", "EE hits .gt. 0.5 SumE VS Eta", nEta, lowEta, highEta, 0., 500.); 
  ee5SumETVSeta_ = fs->make<TProfile>( "ee5SumETVSeta", "EE hits .gt. 0.5 SumET VS Eta", nEta, lowEta, highEta, 0., 500.); 

  Char_t histo1[200];
  Char_t histo2[200];

  for ( unsigned int iDF=0; iDF < 10; iDF++ ) {
    sprintf (histo1, "ee1ADC%02d", iDF+1) ;
    sprintf (histo2, "EE ADC .gt. 0.1 %02d", iDF+1) ;
    ee1DigiADC_.push_back(fs->make<TH1F>( histo1, histo2, 100, 0., 1000. )); 
    sprintf (histo1, "ee1Gain%02d", iDF+1) ;
    sprintf (histo2, "EE Gain .gt. 0.1 %02d", iDF+1) ;
    ee1DigiGain_.push_back(fs->make<TH1F>( histo1, histo2, 4, 0., 4. )); 
    sprintf (histo1, "ee5ADC%02d", iDF+1) ;
    sprintf (histo2, "EE ADC .gt. 0.5 %02d", iDF+1) ;
    ee5DigiADC_.push_back(fs->make<TH1F>( histo1, histo2, 100, 0., 1000. )); 
    sprintf (histo1, "ee5Gain%02d", iDF+1) ;
    sprintf (histo2, "EE Gain .gt. 0.5 %02d", iDF+1) ;
    ee5DigiGain_.push_back(fs->make<TH1F>( histo1, histo2, 4, 0., 4. )); 
  }

  ee1FrameProfile_ = fs->make<TProfile>( "ee1FrameProfile", "EE hits .gt. 0.1 frame profile", 10, 0., 10., 0., 1000.); 
  ee1FrameProfileNoPed_ = fs->make<TProfile>( "ee1FrameProfileNoPed", "EE hits .gt. 0.1 frame profile no ped", 10, 0., 10., 0., 1000.); 
  ee5FrameProfile_ = fs->make<TProfile>( "ee5FrameProfile", "EE hits .gt. 0.5 frame profile", 10, 0., 10., 0., 1000.); 
  ee5FrameProfileNoPed_ = fs->make<TProfile>( "ee5FrameProfileNoPed", "EE hits .gt. 0.5 frame profile no ped", 10, 0., 10., 0., 1000.); 

  ee1SumETVSvtx_ = fs->make<TProfile>( "ee1SumETVSvtx", "EE hits .gt. 0.1 SumET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 
  ee5SumETVSvtx_ = fs->make<TProfile>( "ee5SumETVSvtx", "EE hits .gt. 0.5 SumET VS Vtx", numvtx, 0., (float)numvtx, 0., 500.); 

  for ( int iVtx = 0; iVtx <= numvtx; iVtx++ ) {
    sprintf (histo1, "ee1SumETvtx%02d", iVtx) ;
    sprintf (histo2, "EE hits sum e_T .gt. 0.1 vtx %02d", iVtx) ;
    ee1SumETvtxHisto_.push_back(fs->make<TH1F>( histo1, histo2, 500, 0., 500. )); 
    sprintf (histo1, "ee5SumETvtx%02d", iVtx) ;
    sprintf (histo2, "EE hits sum e_T .gt. 0.5 vtx %02d", iVtx) ;
    ee5SumETvtxHisto_.push_back(fs->make<TH1F>( histo1, histo2, 500, 0., 500. )); 
  }

}

EcalMinBiasAnalysis::~EcalMinBiasAnalysis() {}

void EcalMinBiasAnalysis::beginJob()
{
}

void EcalMinBiasAnalysis::endJob(){return;}
void EcalMinBiasAnalysis::beginRun(const edm::Run& iRun,const edm::EventSetup& iSetup)
{
}
void EcalMinBiasAnalysis::endRun(const edm::Run& iRun,const edm::EventSetup& iSetup){return;}
void EcalMinBiasAnalysis::analyze(const edm::Event& iEvent,const edm::EventSetup& iSetup)
{ 

  edm::Handle<reco::VertexCollection> vtxCollection;
  iEvent.getByLabel(recoVertexCollection_, vtxCollection );
  
  unsigned int nVtx = 0;
  for ( unsigned int iloop = 0; iloop < (*vtxCollection).size(); iloop++ ) {
    if ( (*vtxCollection)[iloop].ndof() > 4 ) { nVtx++; }
  }

  vtxHisto_->Fill((float)nVtx);
    
  edm::Handle< edmNew::DetSetVector<SiPixelCluster> > pixcluCollection;
  iEvent.getByLabel(pixelClusterCollection_, pixcluCollection );
  
  unsigned int nPixClu = (*pixcluCollection).size();
  
  pixcluHisto_->Fill((float)nPixClu);
  
  edm::Handle< EBRecHitCollection > ebRHCollection;
  iEvent.getByLabel(ebRecHitCollection_, ebRHCollection );
  
  unsigned int neb = (*ebRHCollection).size();
    
  edm::Handle< EERecHitCollection > eeRHCollection;
  iEvent.getByLabel(eeRecHitCollection_, eeRHCollection );
  
  unsigned int nee = (*eeRHCollection).size();
      
  if ( (int)nVtx == vtxSel_ ) { edm::LogInfo("EcalMinimumBiasInfo") << iEvent.id() << " # Vtx = " << nVtx << " # SiPixClu = " << nPixClu << " # EB = " << neb << " # EE = " << nee ; }
  
  edm::ESHandle<CaloGeometry> pG;
  iSetup.get<CaloGeometryRecord>().get(pG);     

  edm::ESHandle<EcalChannelStatus> chanstat;
  iSetup.get<EcalChannelStatusRcd>().get(chanstat);
  const EcalChannelStatus* cstat=chanstat.product();      

  std::vector<float> sumh1ET(numvtx+1,0.);
  std::vector<float> sumh5ET(numvtx+1,0.);
  std::vector<float> sumh15ET(numvtx+1,0.);
  
  std::vector<float> sum1Eeta(nEta,0.);
  std::vector<float> sum1ETeta(nEta,0.);
  std::vector<float> sum5Eeta(nEta,0.);
  std::vector<float> sum5ETeta(nEta,0.);
  
  for (EcalRecHitCollection::const_iterator myRecHit = eeRHCollection->begin(); myRecHit != eeRHCollection->end() ; ++myRecHit) {

    // Quality selection on ECAL rec hits

    Bool_t is_spike=false;
    if (myRecHit->checkFlag(EcalRecHit::kWeird) || myRecHit->checkFlag(EcalRecHit::kDiWeird)) is_spike=true;

    int chanstatus=-1;
    EcalChannelStatus::const_iterator chIt = cstat->find( myRecHit->id() );
    if ( chIt != cstat->end() ) {
      chanstatus = chIt->getStatusCode() & 0x1F;
    }
    if (is_spike || chanstatus!=0) continue;

    EEDetId myEEiD(myRecHit->id());
    double cellEta = std::fabs(pG->getPosition(myEEiD).eta());
    double tgThetaH = std::exp(-1.*cellEta);
    double sinTheta = 2.*tgThetaH/(1.+tgThetaH*tgThetaH);
    double hE = myRecHit->energy();
    double hET = hE*sinTheta;

    if ( (int)nVtx <= numvtx ) {
      if ( hET > 0.1 ) {sumh1ET[nVtx] += hET; }
      if ( hET > 0.5 ) {sumh5ET[nVtx] += hET; }
      if ( hET > 0.1 && hET <= 0.5 ) {sumh15ET[nVtx] += hET; }
    }
    
    if ( (int)nVtx == vtxSel_ ) {
      
      // ENDCAP
      
      edm::Handle<EEDigiCollection> EcalDigiEE;
      iEvent.getByLabel( eeDigiCollection_ , EcalDigiEE );
      if( EcalDigiEE.isValid() ) {
        edm::LogInfo("EcalMinimumBiasInfo") << "BX = " << iEvent.bunchCrossing(); 
        edm::LogInfo("EcalMinimumBiasInfo") << "# EE digis = " << EcalDigiEE->size();
      }

      edm::ESHandle<EcalPedestals>            dbPed   ;
      iSetup.get<EcalPedestalsRcd>().get( dbPed ) ;
      const EcalPedestals* pedestals        ( dbPed.product() ) ;      
      EcalPedestalsMap::const_iterator itped = pedestals->getMap().find( myRecHit->id() );

      double hTime = myRecHit->time();
      double hChi2 = myRecHit->chi2();

      int ietaBin = (int)((float)nEta/(highEta-lowEta)*(cellEta-lowEta));
      ietaBin = (ietaBin < nEta) ? ietaBin : nEta-1; 

      eehitEneAllHisto_->Fill(hE);

      if ( hET > 0.1 ) {

        eehit1EtaHisto_->Fill(cellEta);
        eehit1EneHisto_->Fill(hE);
        eehit1ETHisto_->Fill(hET);
        eehit1TimeHisto_->Fill(hTime);
        eehit1Chi2Histo_->Fill(hChi2);

        ee1TimeVSEneHisto_->Fill(hE,hTime);

        sum1Eeta[ietaBin] += hE;
        sum1ETeta[ietaBin] += hET;

        if( EcalDigiEE.isValid() ) {
          const EEDigiCollection * endcapDigi = EcalDigiEE.product () ;
          EcalDigiCollection::const_iterator itr = endcapDigi->find(myEEiD);
          if ( itr != endcapDigi->end() ) {
            for ( unsigned int iDF=0; iDF < 10; iDF++ ) {
              EcalMGPASample mySample((*itr)[iDF]);
              double ped   = (*itped).mean(mySample.gainId());
              ee1DigiADC_[iDF]->Fill(mySample.adc()-ped);
              ee1DigiGain_[iDF]->Fill(mySample.gainId());
              ee1FrameProfile_->Fill((float)iDF+0.5,(float)mySample.adc());
              ee1FrameProfileNoPed_->Fill((float)iDF+0.5,(float)mySample.adc()-ped);
              //              std::cout << (float)iDF+0.5 << " " << mySample.adc() << " " << mySample.adc()-ped << std::endl;
            }
          }
        }

        if ( hET > 0.5 ) {

          eehit5EtaHisto_->Fill(cellEta);
          eehit5EneHisto_->Fill(hE);
          eehit5ETHisto_->Fill(hET);
          eehit5TimeHisto_->Fill(hTime);
          eehit5Chi2Histo_->Fill(hChi2);

          ee5TimeVSEneHisto_->Fill(hE,hTime);
        
          sum5Eeta[ietaBin] += hE;
          sum5ETeta[ietaBin] += hET;
          
          if( EcalDigiEE.isValid() ) {
            const EEDigiCollection * endcapDigi = EcalDigiEE.product () ;
            EcalDigiCollection::const_iterator itr = endcapDigi->find(myEEiD);
            if ( itr != endcapDigi->end() ) {
              for ( unsigned int iDF=0; iDF < 10; iDF++ ) {
                EcalMGPASample mySample((*itr)[iDF]);
                double ped   = (*itped).mean(mySample.gainId());
                ee5DigiADC_[iDF]->Fill(mySample.adc()-ped);
                ee5DigiGain_[iDF]->Fill(mySample.gainId());
                ee5FrameProfile_->Fill((float)iDF+0.5,(float)mySample.adc());
                ee5FrameProfileNoPed_->Fill((float)iDF+0.5,(float)mySample.adc()-ped);
              }
            }
          }

        }
        
      }

    }

  }

  if ( (int)nVtx == vtxSel_ ) {
      
    ebmultiHisto_->Fill((float)neb);
    eemultiHisto_->Fill((float)nee);
    
    eehit1SumETHisto_->Fill(sumh1ET[vtxSel_]);
    eehit5SumETHisto_->Fill(sumh5ET[vtxSel_]);
    eehit15SumETHisto_->Fill(sumh15ET[vtxSel_]);
    
    for ( int ibin = 0; ibin < nEta; ibin++ ) {
      float eta = lowEta+(float)ibin*(highEta-lowEta)/(float)nEta;
      ee1SumEVSeta_->Fill(eta,sum1Eeta[ibin]);
      ee1SumETVSeta_->Fill(eta,sum1ETeta[ibin]);
      ee5SumEVSeta_->Fill(eta,sum5Eeta[ibin]);
      ee5SumETVSeta_->Fill(eta,sum5ETeta[ibin]);
    }
  }

  if ( (int)nVtx <= numvtx ) {
    ee1SumETVSvtx_->Fill((float)nVtx,sumh1ET[nVtx]);
    ee5SumETVSvtx_->Fill((float)nVtx,sumh5ET[nVtx]);
    ee1SumETvtxHisto_[nVtx]->Fill(sumh1ET[nVtx]);
    ee5SumETvtxHisto_[nVtx]->Fill(sumh5ET[nVtx]);
  }


}//analyze


//define this as a plug-in
DEFINE_FWK_MODULE(EcalMinBiasAnalysis);
