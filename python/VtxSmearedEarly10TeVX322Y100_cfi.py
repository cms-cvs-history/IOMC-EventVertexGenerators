import FWCore.ParameterSet.Config as cms

from IOMC.EventVertexGenerators.VtxSmearedParameters_cfi import *
VtxSmeared = cms.EDFilter("BetafuncEvtVtxGenerator",
    Early10TeVX322Y100VtxSmearingParameters,
    VtxSmearedCommon
)


