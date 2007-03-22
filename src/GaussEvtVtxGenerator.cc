
// $Id: GaussEvtVtxGenerator.cc,v 1.2 2006/11/07 19:38:47 wdd Exp $

#include "IOMC/EventVertexGenerators/interface/GaussEvtVtxGenerator.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CLHEP/Random/RandGauss.h"
#include "CLHEP/Units/SystemOfUnits.h"
//#include "CLHEP/Vector/ThreeVector.h"
#include "HepMC/SimpleVector.h"

GaussEvtVtxGenerator::GaussEvtVtxGenerator(const edm::ParameterSet & p )
: BaseEvtVtxGenerator(p)
{ 
  
  fRandom = new CLHEP::RandGauss(getEngine());
  
  fMeanX =  p.getParameter<double>("MeanX")*cm;
  fMeanY =  p.getParameter<double>("MeanY")*cm;
  fMeanZ =  p.getParameter<double>("MeanZ")*cm;
  fSigmaX = p.getParameter<double>("SigmaX")*cm;
  fSigmaY = p.getParameter<double>("SigmaY")*cm;
  fSigmaZ = p.getParameter<double>("SigmaZ")*cm;

  if (fSigmaX < 0) {
    throw cms::Exception("Configuration")
      << "Error in GaussEvtVtxGenerator: "
      << "Illegal resolution in X (SigmaX is negative)";
  }
  if (fSigmaY < 0) {
    throw cms::Exception("Configuration")
      << "Error in GaussEvtVtxGenerator: "
      << "Illegal resolution in Y (SigmaY is negative)";
  }
  if (fSigmaZ < 0) {
    throw cms::Exception("Configuration")
      << "Error in GaussEvtVtxGenerator: "
      << "Illegal resolution in Z (SigmaZ is negative)";
  }
}

GaussEvtVtxGenerator::~GaussEvtVtxGenerator() 
{
  delete fRandom; 
}

//Hep3Vector* GaussEvtVtxGenerator::newVertex() {
HepMC::FourVector* GaussEvtVtxGenerator::newVertex() {
  double X,Y,Z;
  X = fSigmaX * fRandom->fire() + fMeanX ;
  Y = fSigmaY * fRandom->fire() + fMeanY ;
  Z = fSigmaZ * fRandom->fire() + fMeanZ ;

  //if (fVertex == 0) fVertex = new CLHEP::Hep3Vector;
  if ( fVertex == 0 ) fVertex = new HepMC::FourVector() ;
  fVertex->set( X, Y, Z, 0. ) ;

  return fVertex;
}

void GaussEvtVtxGenerator::sigmaX(double s) 
{ 
  if (s>=0 ) {
    fSigmaX=s; 
  }
  else {
    throw cms::Exception("LogicError")
      << "Error in GaussEvtVtxGenerator::sigmaX: "
      << "Illegal resolution in X (negative)";
  }
}

void GaussEvtVtxGenerator::sigmaY(double s) 
{ 
  if (s>=0 ) {
    fSigmaY=s; 
  }
  else {
    throw cms::Exception("LogicError")
      << "Error in GaussEvtVtxGenerator::sigmaY: "
      << "Illegal resolution in Y (negative)";
  }
}

void GaussEvtVtxGenerator::sigmaZ(double s) 
{ 
  if (s>=0 ) {
    fSigmaZ=s; 
  }
  else {
    throw cms::Exception("LogicError")
      << "Error in GaussEvtVtxGenerator::sigmaZ: "
      << "Illegal resolution in Z (negative)";
  }
}
