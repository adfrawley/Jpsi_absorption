#include <iostream>
#include <fstream>
#include <TCanvas.h>
#include <TH1D.h>

void process_bu_mod_error_estimate_output()
{
  static const int NCENT = 7;

  // seven centralities max
  // 4 rapidities in south arm
  TH1D *h[7][4];
  for(int icent=0; icent<NCENT; ++icent)
    {
      for(int irap=0;irap<4;irap++)
	{
	  char hname[500];
	  sprintf(hname,"h%i%i",icent,irap);
	  h[icent][irap] = new TH1D("hname", "", 100, 0.4, 1.0);
	}
    }

  for (int i=0;i<1000;++i)
    {
      char fname[500];
      sprintf(fname,"estimate_output/BU_mod_%i",i);
      //sprintf(fname,"pAu_mod_error_estimate_output/BU_mod_%i",i);
      //sprintf(fname,"pAl_mod_error_estimate_output/BU_mod_%i",i);
      cout << "Open file " << fname << endl;

      ifstream fin(fname);

      if(!fin.is_open())
	{
      	  cout << " failed to open file " << fname << endl;
	  continue;
	}
      
      double y, s1, r0, vcc, mod;
      int cent;

      for(int j=0;j<4;++j)
	{
	  for(int icent=0;icent<NCENT;++icent)
	    {
	      fin >> y >> cent >> s1 >> r0 >> vcc >> mod;
	      //cout << " y " << y << " cent " << cent << " s1 " << s1 << " r0 " << r0 << " vcc " << vcc << " mod " << mod << endl;  
	      h[icent][j]->Fill(mod);
	    }
	}
    }

  TCanvas *c[NCENT];
  for(int icent=0;icent<NCENT; ++icent)
    {
      char cname[500];
      sprintf(cname,"c%i",icent);
      c[icent] = new TCanvas(cname,cname, 5,5,1200,800);
      c[icent]->Divide(2,2);

      for(int i=0; i<4; ++i)
	{
	  c[icent]->cd(i+1);
	  h[icent][i]->Draw();
	}
    }
}
