import FWCore.ParameterSet.Config as cms

process = cms.Process("ecalMinBiasAnalysis")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'GR_P_V43::All', '')

process.maxEvents = cms.untracked.PSet(
#    input = cms.untracked.int32(-1)
    input = cms.untracked.int32(100)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/005A9FC8-B4FA-E111-95B7-00215AEDFD74.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/10E458BA-8DFA-E111-A3B8-5404A6388699.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/149E28D5-6CFA-E111-BB39-003048D37560.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/2214FD4B-6BFA-E111-BEE2-002481E0DEC6.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/304F0D26-83FA-E111-9CB7-001D09F27003.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/32447A0B-85FA-E111-863E-001D09F24664.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/3606A53B-6EFA-E111-8B26-001D09F2B2CF.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/3A10933A-6EFA-E111-A729-003048D2BC42.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/5ABC64C9-82FA-E111-8F18-001D09F2AD84.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/6634203F-6EFA-E111-B760-001D09F253C0.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/68411F07-93FA-E111-86E9-BCAEC53296F7.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/6A79E568-8BFA-E111-9F3D-001D09F2447F.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/7A42E9E9-78FA-E111-A412-001D09F28F25.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/82D571A1-8EFA-E111-81D8-00237DDC5C24.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/921950B7-6EFA-E111-9AF8-5404A63886EC.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/9A5942F2-7BFA-E111-B54E-BCAEC518FF8A.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/B2A28D98-88FA-E111-9FF0-0025B3203898.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/B81CF364-6DFA-E111-911E-003048F24A04.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/BA1899BA-69FA-E111-9212-003048F024FA.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/C46CA037-6EFA-E111-8D46-001D09F24D8A.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/D4C813CF-6FFA-E111-B8FF-001D09F24303.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/E6143A03-8FFA-E111-94B7-0019B9F4A1D7.root',
                                      '/store/data/Run2012C/MinimumBias/RECO/PromptReco-v2/000/202/299/FE8A5D0A-90FA-E111-AF91-001D09F29533.root')
#   fileNames = cms.untracked.vstring('file:164D2525-0DFD-E111-A3A5-485B39800C3B.root')
#   fileNames = cms.untracked.vstring('file:step3.root')
)


process.level1Pattern = cms.EDFilter('HLTLevel1Pattern',
                                     L1GtReadoutRecordTag = cms.InputTag('gtDigis'),
                                     triggerBit = cms.string('L1Tech_BPTX_plus_AND_minus.v0'),
                                     daqPartitions = cms.uint32(1),
                                     ignoreL1Mask = cms.bool(True),
                                     invert = cms.bool(False),
                                     throw = cms.bool(True),
                                     bunchCrossings = cms.vint32( -2, -1,  0,  1,  2 ),
                                     triggerPattern = cms.vint32(  0,  0,  1,  0,  1 )
#                                     triggerPattern = cms.vint32(  1,  0,  1,  0,  1 )
#                                     triggerPattern = cms.vint32(  1,  0,  1,  0,  0 )
)

process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.HLTPaths = cms.vstring("HLT_ZeroBias_v*")
#process.hltHighLevel.HLTPaths = cms.vstring("HLT_Physics_v*")
#process.hltHighLevel.HLTPaths = cms.vstring("HLT_L1Tech53_MB_2_v*")
#for LP_MinBias2 datasample

process.load('CommonTools/RecoAlgos/HBHENoiseFilter_cfi')
process.load('RecoMET.METFilters.eeBadScFilter_cfi')

process.noscraping = cms.EDFilter("FilterOutScraping",
                                  applyfilter = cms.untracked.bool(True),
                                  debugOn = cms.untracked.bool(False),
                                  numtrack = cms.untracked.uint32(10),
                                  thresh = cms.untracked.double(0.25)
)


process.primaryVertexFilter = cms.EDFilter("GoodVertexFilter",
                                           vertexCollection =
                                           cms.InputTag('offlinePrimaryVertices'),
                                           minimumNDOF = cms.uint32(4) ,
                                           maxAbsZ = cms.double(24),
                                           maxd0 = cms.double(2)
)

# Unpacking of RAW, only of present 
process.load('SimCalorimetry.EcalTrigPrimProducers.ecalTriggerPrimitiveDigis_cff')
process.load('EventFilter.EcalRawToDigi.EcalUnpackerData_cfi')
process.ecalDigis = process.ecalEBunpacker.clone()
process.ecalDigis.InputLabel = cms.InputTag('rawDataCollector')


process.load("UserCode.fabiocos.EcalMinBiasAnalysis_cfi")

process.MessageLogger.categories=cms.untracked.vstring('FwkJob'
                                                      ,'FwkReport'
                                                      ,'FwkSummary'
                                                      ,'Root_NoDictionary'
                                                      ,'EcalMinimumBiasInfo'
)
    

process.MessageLogger.cerr.INFO = cms.untracked.PSet(limit = cms.untracked.int32(0))
process.MessageLogger.cerr.EcalMinimumBiasInfo = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)

process.TFileService = cms.Service("TFileService", fileName = cms.string("ecalMinBiasAnalysis_histo.root") )

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#process.p = cms.Path(process.level1Pattern * process.hltHighLevel *
process.p = cms.Path(process.hltHighLevel *
                     process.primaryVertexFilter * process.noscraping *
                     process.HBHENoiseFilter * process.eeBadScFilter *
#                     process.ecalDigis *
                     process.ecalMinBiasAnalysis)
# in MC I don't include the process.hltHighLevel in the sequence




