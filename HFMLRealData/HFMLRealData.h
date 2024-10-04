#ifndef __HFMLRealData_H__
#define __HFMLRealData_H__

// --- need to check all these includes...
#include <fun4all/SubsysReco.h>
#include <limits.h>
#include <cmath>
#include <fstream>  // std::fstream
#include <string>
#include <vector>
#include <map>
#include <g4main/PHG4VtxPoint.h>
#include <trackbase/ActsGeometry.h>
#include <trackbase/TrkrHitSetContainer.h>
#include <trackbase/TrkrHitSet.h>


class TTree;
class TFile;
class TH2F;
class TH3F;

class PdbParameterMap;
class PHCompositeNode;
class PHG4CylinderGeomContainer;
class PHG4HitContainer;
class PHHepMCGenEventMap;
class PHG4TruthInfoContainer;
class PHG4Hit;
class SvtxEvalStack;
//class TrkrClusterHitAssoc;
class TrkrHitSetContainer;
class TrkrHitTruthAssoc;

class TrackSeedContainer;
class TrkrClusterContainer;

namespace HepMC
{
class GenEvent;
}

class HFMLRealData : public SubsysReco
{
 public:
  HFMLRealData(std::string filename);

  int Init(PHCompositeNode *);
  int InitRun(PHCompositeNode *);
  int process_event(PHCompositeNode*);
  int End(PHCompositeNode *);
  int load_nodes(PHCompositeNode *);

 private:



  int Event;
  std::fstream m_jsonOut;

  std::string _foutname = "Data.json";
  TrkrHitSetContainer *m_hitsets = NULL;
  TrkrClusterContainer *m_clus = NULL;
  TrackSeedContainer *m_si_seeds = NULL;

 
  unsigned int _nlayers_maps = 3;
  int hitID;
  int hitIDINTT;
  ActsGeometry * actsGeom;
  PHG4CylinderGeomContainer *m_Geoms;
  PHG4CylinderGeomContainer *m_Geoms2;


  //TrkrHitSetContainer *m_hitsets;

};

#endif  // __HFMLRealData_H___

#include <trackbase/TrkrHitSetContainer.h>
