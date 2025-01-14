#ifndef ADV_H
#define ADV_H

#include "gui/gui.h"
#include "resource/resources.h"

#include "base.h"
#include "skills.h"

class mapCell;
extern class town;
extern class fullMap;

#define ORIG_SPELLS 65

#pragma pack(push, 1)

#define MAX_TOTAL_HEROES 48

#define CREATURES_IN_ARMY 5

#define NUM_RESOURCES 7
#define NUM_SECONDARY_RESOURCES 6


enum RESOURCES {
  RESOURCE_WOOD = 0,
  RESOURCE_MERCURY = 1,
  RESOURCE_ORE = 2,
  RESOURCE_SULFUR = 3,
  RESOURCE_CRYSTAL = 4,
  RESOURCE_GEMS = 5,
  RESOURCE_GOLD = 6,
};

class armyGroup {
public:
  char creatureTypes[CREATURES_IN_ARMY];
  __int16 quantities[CREATURES_IN_ARMY];

  armyGroup() {
    for (int i = 0; i < ELEMENTS_IN(this->creatureTypes); i++) {
      this->creatureTypes[i] = -1;
    }

    for (int i = 0; i < ELEMENTS_IN(this->quantities); i++) {
      this->quantities[i] = 0;
    }
  };

  int Add(int, int, int);
  void ClearArmy();
  
};

class hero {
public:
  __int16 spellpoints;
  char idx;
  char ownerIdx;
  char field_4;
  char field_5;
  char field_6;
  char field_7;
  char field_8;
  char field_9;
  char name[13];
  char factionID;
  char heroID;
  int x;
  int y;
  __int16 field_21;
  __int16 field_23;
  __int16 field_25;
  __int16 field_27;
  __int8 relatedToX;
  __int8 relatedToY;
  __int8 relatedToFactionID;
  __int8 relatedToUnknown;
  __int16 occupiedObjType;
  __int16 occupiedObjVal;
  int mobility;
  int remainingMobility;
  int experience;
  __int16 oldLevel;
  char primarySkills[NUM_PRIMARY_SKILLS];
  char field_43;
  char tempMoraleBonuses;
  char tempLuckBonuses;
  char field_46;
  int gazeboesVisited;
  int fortsVisited;
  int witchDoctorHutsVisited;
  int mercenaryCampsVisited;
  int standingStonesVisited;
  int treesOfKnowledgeVisited;
  int xanadusVisited;
  char randomSeed;
  char wisdomLastOffered;
  armyGroup army;
  char secondarySkillLevel[14];
  char skillIndex[14];
  int numSecSkillsKnown;

  /*
   * In order to put more space in the hero class for new spells,
   * we would need to decompile virtually the entire codebase, as doing so would also
   * change the size of the game class.
   *
   * We instead replace the statically-allocated spellsLearned array with a pointer to a dynamically-allocated one,
   * so that we only need to decompile the direct accesses.
   *
   * There ARE memory leaks associated with doing this. We've done much of what we can to avoid this,
   * but there's no easy way out, and the leak is upper-bounded by 3 kb every time you load a map
   */
   //char spellsLearned[65];
  char* spellsLearned;
  char _[ORIG_SPELLS - sizeof(char*)];

#define FIELD_AFTER_SPELLS_LEARNED artifacts
  char artifacts[14];
  int flags;
  char isCaptain;
  int field_E8;
#define LAST_SW_HERO_FIELD scrollSpell
  char scrollSpell[14];

  hero();
  ~hero(); //newly added
  void AddSpell(int);
  void AddSpell(int, int);
  int HasSpell(int);
  int GetNumSpells(int);
  int GetNthSpell(int, int);
  void UseSpell(int);

  int HasArtifact(int);
  void TakeArtifact(int);
  int CountEmptyArtifactSlots();
  int CountEmptyCreatureSlots();
  signed char Stats(int);
  signed char GetSSLevel(int);
  void SetSS(int, int);
  void CheckLevel();
  int GiveSS(int, int);
  void ClearSS();
  int CalcMobility();
  int CalcMobility_orig();

  void Read(int, signed char);
  void ResetSpellsLearned();

  void SetPrimarySkill(int, int);
  int GetLevel();
  void Clear();
  int NumArtifacts();
};

enum HERO_FLAGS {
  HERO_AT_SEA = 0x80,
  HERO_FLAG_RELATED_TO_PYRAMID = 0x4000,
  HERO_ARMY_COMPACT = 0x8000
};

extern char cHeroTypeInitial[];
extern signed __int8 captainStats[][NUM_PRIMARY_SKILLS];

class mapCell;

class advManager : public baseManager {
public:
  int field_36;
  widget *someComponents[2][12];
  heroWindow *adventureScreen;
  int sizeOfSomethingMapRelated;
  int field_A2;
  int currentTerrain;
  int field_AA;
  fullMap *map;
  iconWidget *heroScrollbarKnob;
  iconWidget *castleScrollbarKnob;
  int field_BA;
  int field_BE;
  tileset *groundTileset;
  tileset *clofTileset;
  tileset *stonTileset;
  int field_CE[64];
  icon *radarIcon;
  icon *clopIcon;
  int viewX;
  int viewY;
  int field_1DE;
  int field_1E2;
  int xOff;
  int yOff;
  char _2[0xB8];
  int heroMobilized;
  char _3[0xD4];

  advManager();

  mapCell *GetCell(int x, int y);

  void EraseObj(mapCell*, int x, int y);

  void PurgeMapChangeQueue();
  void CheckSetEvilInterface(int, int);

  void DemobilizeCurrHero();

  void DimensionDoor();
  void TeleportTo(hero*, int, int, int, int);

  void CastSpell(int);
  void CastSpell_orig(int);

  void CompleteDraw(int);
  void RedrawAdvScreen(int, int);
  void UpdateRadar(int, int);
  void UpdateHeroLocator(int, int, int);
  void UpdBottomView(int, int, int);
  void EventSound(int locType, int locType2, SAMPLE2 *samp);

  void __thiscall EventWindow(int, int, char *, int, int, int, int, int);
  void __thiscall UpdateHeroLocators(int, int);
  void __thiscall UpdateScreen(int, int);
  void UpdateTownLocators(int a2, int updateScreen);

  int ProcessDeSelect(struct tag_message *GUIMessage_evt, int *a3, class mapCell **a4);
  int ProcessDeSelect_orig(struct tag_message *, int *, class mapCell **);

  virtual int Open(int);
  int Open_orig(int);

  void PasswordEvent(mapCell *tile, hero *hero);
  int BarrierEvent(mapCell *tile, hero *hero);

  void ExpansionRecruitEvent(class hero*, int, short*);

  mapCell* MoveHero(int, int, int *, int *, int *, int, int *, int);
  mapCell* MoveHero_orig(int, int, int *, int *, int *, int, int *, int);

  void DoEvent_orig(class mapCell *, int, int);
  void DoEvent(class mapCell *cell, int locX, int locY);

  void HandleSpellShrine(class mapCell *cell, int LocationType, hero *hro, SAMPLE2 *res2, int locX, int locY);
  void HandlePyramid(class mapCell *cell, int LocationType, hero *hro, SAMPLE2 *res2, int locX, int locY);

  int CombatMonsterEvent(class hero *hero, int mon1, int mon1quantity, class mapCell *mapcell, int locX, int locY, int switchSides, int locX2, int locY2, int mon2, int mon2quantity, int mon2stacks, int mon3, int mon3quantity, int mon3stacks);
  int MapPutArmy(int x, int y, int monIdx, int monQty);

  int GiveExperience(class hero*, int, int);

  void QuickInfo(int, int);
  void QuickInfo_orig(int, int);

  void PlayerMonsterInteract(mapCell *cell, mapCell *other, hero *player, int *window, int a1, int a2, int a3, int a4, int a5);
  void PlayerMonsterInteract_orig(mapCell *cell, mapCell *other, hero *player, int *window, int a1, int a2, int a3, int a4, int a5);

  void ComputerMonsterInteract(mapCell *cell, hero *computer, int *a1);
  void ComputerMonsterInteract_orig(mapCell *cell, hero *computer, int *a1);

  void TownQuickView(int a2, int a3, int a4, int a5);
  int IsCrystalBallInEffect(int x, int y, int a3);
  void SetTownContext(int townID);
  char * GetArmySizeName(signed int amt, int queryType);
  char * GetQuantityString(int thievesGuildsLevel, town* town, int garrisonIdx);
};

class ExpCampaign {
public:

  ExpCampaign();

  char HasAward(int a2);
  char *JosephName();
  char *IvanName();
  
};

extern advManager* gpAdvManager;

extern int giMapChangeCtr;

extern heroWindow* heroWin;
extern int giHeroScreenSrcIndex;

extern int giAdjacentMonsterUpperBoundX;
extern int giAdjacentMonsterUpperBoundY;
extern int giAdjacentMonsterX;
extern int giAdjacentMonsterY;
extern int giAdjacentMonsterLowerBoundX;
extern int giAdjacentMonsterLowerBoundY;
extern ExpCampaign xCampaign;

hero* GetCurrentHero();
bool GetMapCellXY(mapCell* cell, int* x, int* y);

int __fastcall GiveArtifact(hero*, int artifact, int checkEndGame, signed char scrollSpell);
void __fastcall GiveTakeArtifactStat(hero *h, int art, int take);
void __fastcall GetMonsterCost(int, int * const);

#pragma pack(pop)

#endif
