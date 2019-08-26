for (int ntof = 0; ntof < MAXTOFCH; ntof++){
  for (int nesd = 0; nesd < MAXESDCH; nesd++){

    float max = 0.0;
    int smax  = 0;
    for (int s = 0; s < grp.size(); s++){
      if (P[s][ntof][nesd] > max){
	max = P[s][ntof][nesd];
	smax = s;
      }
    }

    NprobMax[nedb][smax] += MA.getElement(nedb,ntof,nesd);
    sum += NprobMax[nedb][s];

  }
}
