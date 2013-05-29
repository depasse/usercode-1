import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

### conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'START53_V15A::All'

### standard includes
process.load('Configuration/StandardSequences/Services_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

process.load("RecoTracker.TrackProducer.TrackRefitters_cff")

process.load("HLTrigger.HLTfilters.triggerResultsFilter_cfi")
process.MinBias_Trigger = process.triggerResultsFilter.clone()
#process.MinBias_Trigger.triggerConditions = cms.vstring('HLT_*',)
process.MinBias_Trigger.triggerConditions = cms.vstring('HLT_L1SingleJet16_v6',)
process.MinBias_Trigger.hltResults = cms.InputTag( "TriggerResults", "", "HLT" )
process.MinBias_Trigger.l1tResults = cms.InputTag("")
process.MinBias_Trigger.throw = cms.bool( False )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring('/store/relval/CMSSW_5_3_6-START53_V14/RelValMinBias/GEN-SIM-RECO/v2/00000/B49ED161-2A2A-E211-913F-00304867916E.root')
)

process.demo = cms.EDAnalyzer('TrackTest',
        tracks = cms.untracked.InputTag('TrackRefitter'),
        TTRHBuilder = cms.string('WithAngleAndTemplate')
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("tracktest_histo.root") )

process.MessageLogger.categories=cms.untracked.vstring('FwkJob'
                                                      ,'FwkReport'
                                                      ,'FwkSummary'
                                                      ,'Root_NoDictionary'
                                                      ,'TrackInfo'
                                                      ,'HitInfo'
)
    

process.MessageLogger.cerr.INFO = cms.untracked.PSet(limit = cms.untracked.int32(0))
process.MessageLogger.cerr.TrackInfo = cms.untracked.PSet(limit = cms.untracked.int32(0))
process.MessageLogger.cerr.HitInfo = cms.untracked.PSet(limit = cms.untracked.int32(0))
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)
process.MessageLogger.cerr.FwkReport.reportEvery = 999999999
process.MessageLogger.categories.append('HLTrigReport')

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.p = cms.Path(process.MinBias_Trigger*process.TrackRefitter*process.demo)
