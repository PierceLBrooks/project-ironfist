{
  signed int v3; // ST10_4@19
  int tries; // [sp+14h] [bp-8h]@1
  int randArtifact; // [sp+18h] [bp-4h]@3

  tries = 0;
  while ( 1 )
  {
    if ( xIsExpansionMap )
      randArtifact = Random(0, 102);
    else
      randArtifact = Random(0, 81);
    if ( (unsigned __int8)(gArtifactLevel[randArtifact] & allowedLevels)
      && randArtifact != 82
      && randArtifact != 83
      && randArtifact != 84
      && randArtifact != 85
      && randArtifact != ARTIFACT_SPELL_SCROLL
      && (!xIsPlayingExpansionCampaign
       || randArtifact != ARTIFACT_BREASTPLATE_OF_ANDURAN
       && randArtifact != ARTIFACT_BATTLE_GARB_OF_ANDURAN
       && randArtifact != ARTIFACT_HELMET_OF_ANDURAN
       && randArtifact != ARTIFACT_SWORD_OF_ANDURAN
       && randArtifact != ARTIFACT_SPHERE_OF_NEGATION) )
    {
      v3 = tries++;
      if ( v3 >= 100 || !this->probablyArtifactGeneratedRandomly[randArtifact] )
      {
        if ( (!IsCursedItem((ARTIFACT)randArtifact) || allowNegatives && Random(0, 100) >= 30)
          && (this->winConditionType != 3 || this->winConditionArgument - 1 != randArtifact) )
          break;
      }
    }
  }
  this->probablyArtifactGeneratedRandomly[randArtifact] = 1;
  return randArtifact;
}