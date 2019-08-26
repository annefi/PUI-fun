  // find ONC region
  int onc_tof[] = {0, 0}; // mass (low, high) for ONC region
  int onc_esd[] = {0, 0}; // m/q  (low, high) for ONC region
  int pos;  // tmp holder for position in tof or E space

  vector<int> onc;
  onc.push_back(ad.IonsIndex["C5+"]);
  onc.push_back(ad.IonsIndex["N6+"]);
  onc.push_back(ad.IonsIndex["O6+"]);
  onc.push_back(ad.IonsIndex["O7+"]);
  for (int s = 0; s < ad.Ions.size(); s++){
    for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
      for(int t = 0; t < onc.size(); t++){

	pos = ad.Ions[onc[t]].tof - ad.Ions[onc[t]].stof;
	if (pos < onc_tof[0]){
	  onc_tof[0] = pos;
	}

	pos = ad.Ions[onc[t]].tof + ad.Ions[onc[t]].stof;
	if (pos < onc_tof[1]){
	  onc_tof[1] = pos;
	}

	pos = ad.Ions[onc[t]].esd - ad.Ions[onc[t]].sesd;
	if (pos < onc_esd[0]){
	  onc_esd[0] = pos;
	}

	pos = ad.Ions[onc[t]].esd + ad.Ions[onc[t]].sesd;
	if (pos < onc_esd[1]){
	  onc_esd[1] = pos;
	}

      }
    }
  }
