{
  signed int i; // [sp+10h] [bp-24h]@1
  int arr[7]; // [sp+14h] [bp-20h]@1
  int v4; // [sp+30h] [bp-4h]@4

  getCreatureCosts(a1, arr);
  for ( i = 0; i < 7; ++i )
  {
    if ( arr[i] )
    {
      if ( gpCurPlayer->resources[i] <= 0 )
        v4 = 0;
      else
        v4 = gpCurPlayer->resources[i] / arr[i];
    }
    else
    {
      v4 = 9999;
    }
  }
  return v4;
}