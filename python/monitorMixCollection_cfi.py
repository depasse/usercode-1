import FWCore.ParameterSet.Config as cms

from SimGeneral.MixingModule.mixObjects_cfi import *

monitorMixCollection = cms.EDAnalyzer("MonitorMixCollection",
#    outputFile = cms.string('histosMixCollStandardMM.root'),
    outputFile = cms.string(''),
    minBunch = cms.int32(-2),
    maxBunch = cms.int32(2),
    bunchSpace = cms.double(50.),
    verbose = cms.untracked.bool(False),                                       
    mixObjects = cms.PSet(
        mixCH = cms.PSet(                   
            mixCaloHits                     
        ),                      
        mixTracks = cms.PSet(       
            mixSimTracks                    
        ),                      
        mixVertices = cms.PSet(     
            mixSimVertices                  
        ),                      
        mixSH = cms.PSet(           
            mixSimHits                      
        ),                      
        mixHepMC = cms.PSet(        
            mixHepMCProducts                
        )                       
    )                               
)                                   
