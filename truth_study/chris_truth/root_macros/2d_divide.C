{
TString histFileName = "test.root";
TFile *_file0 = TFile::Open(histFileName, "UPDATE");
//----------------------------------------------------------------------------------//

TH2D *full_scan_bf, *full_scan_ps, *full_scan_fs;

_file0->GetObject("before_cuts/mSUGRA_Scan_Plane;1", full_scan_bf);
_file0->GetObject("preselection_cuts_375_475/mSUGRA_Scan_Plane;1", full_scan_ps);
_file0->GetObject("fullselection_cuts_375_475/mSUGRA_Scan_Plane;1", full_scan_fs);
//----------------------------------------------------------------------------------//
///////////////////////////////////////////////////
//-----------------------//
// Analysis for no cuts  //
//-----------------------//
///////////////////////////////////////////////////

TH2D *scan_bmulti_frac_bf[4], *bmulti_scan_total_bf, *bmulti_scan_bf[4];

TH2D *scan_bmulti_frac_bf[0] = new TH2D("bf_frac_0bs", "bf_frac_0bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_bf[1] = new TH2D("bf_frac_1bs", "bf_frac_1bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_bf[2] = new TH2D("bf_frac_2bs", "bf_frac_2bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_bf[3] = new TH2D("bf_frac_>2bs", "bf_frac_>2bs", 150, 0, 3000, 51, 0, 1020);

TH2D *bmulti_scan_total_bf = new TH2D("total_b_bf", "total_b_bf", 150, 0, 3000, 51, 0, 1020);
TH2D *bmulti_scan_total_frac_bf = new TH2D("total_b_frac_bf", "total_b_frac_bf", 150, 0, 3000, 51, 0, 1020);


_file0->GetObject("before_cuts/b-multi_scan_0;1", bmulti_scan_bf[0]);
_file0->GetObject("before_cuts/b-multi_scan_1;1", bmulti_scan_bf[1]);
_file0->GetObject("before_cuts/b-multi_scan_2;1", bmulti_scan_bf[2]);
_file0->GetObject("before_cuts/b-multi_scan_3;1", bmulti_scan_bf[3]);

bmulti_scan_total_bf->Add(bmulti_scan_bf[1],bmulti_scan_bf[2]);
bmulti_scan_total_bf->Add(bmulti_scan_bf[3]);

cout << "Filling fractions for before any cuts" << endl;

for(Int_t i=0; i<=3; i++){
	scan_bmulti_frac_bf[i]->Divide(bmulti_scan_bf[i], full_scan_bf);
}

bmulti_scan_total_frac_bf->Divide(bmulti_scan_total_bf, full_scan_bf);

//----------------------------------------------------------------------------------//
///////////////////////////////////////////////////
//-----------------------//
// Analysis for ps cuts  //
//-----------------------//
///////////////////////////////////////////////////

TH2D  *scan_bmulti_frac_ps[4], *bmulti_scan_total_ps, *bmulti_scan_ps[4];

TH2D *scan_bmulti_frac_ps[0] = new TH2D("ps_frac_0bs", "ps_frac_0bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_ps[1] = new TH2D("ps_frac_1bs", "ps_frac_1bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_ps[2] = new TH2D("ps_frac_2bs", "ps_frac_2bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_ps[3] = new TH2D("ps_frac_>2bs", "ps_frac_>2bs", 150, 0, 3000, 51, 0, 1020);

TH2D *bmulti_scan_total_ps = new TH2D("total_b_ps", "total_b_ps", 150, 0, 3000, 51, 0, 1020);

TH2D *bmulti_scan_total_frac_ps = new TH2D("total_b_frac_ps", "total_b_frac_ps", 150, 0, 3000, 51, 0, 1020);


_file0->GetObject("preselection_cuts_375_475/b-multi_scan_0;1", bmulti_scan_ps[0]);
_file0->GetObject("preselection_cuts_375_475/b-multi_scan_1;1", bmulti_scan_ps[1]);
_file0->GetObject("preselection_cuts_375_475/b-multi_scan_2;1", bmulti_scan_ps[2]);
_file0->GetObject("preselection_cuts_375_475/b-multi_scan_3;1", bmulti_scan_ps[3]);


cout << "Filling fractions for PreSelection cuts" << endl;

for(Int_t i=0; i<=3; i++){
	scan_bmulti_frac_ps[i]->Divide(bmulti_scan_ps[i], full_scan_ps);
}

// sum 1,2 and >2 plots for 'any' b-quark event
bmulti_scan_total_ps->Add(bmulti_scan_ps[1],bmulti_scan_ps[2]);
bmulti_scan_total_ps->Add(bmulti_scan_ps[3]);

bmulti_scan_total_frac_ps->Divide(bmulti_scan_total_ps, full_scan_ps);

//----------------------------------------------------------------------------------//
///////////////////////////////////////////////////
//-----------------------//
// Anlaysis for fs cuts  //
//-----------------------//
///////////////////////////////////////////////////

TH2D  *full_scan_fs, *scan_bmulti_frac_fs[4];
TH2D  *bmulti_scan_total_fs;
TH2D  *bmulti_scan_fs[4];

TH2D *scan_bmulti_frac_fs[0] = new TH2D("fs_frac_0bs", "fs_frac_0bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_fs[1] = new TH2D("fs_frac_1bs", "fs_frac_1bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_fs[2] = new TH2D("fs_frac_2bs", "fs_frac_2bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_fs[3] = new TH2D("fs_frac_>2bs", "fs_frac_>2bs", 150, 0, 3000, 51, 0, 1020);

TH2D *bmulti_scan_total_fs = new TH2D("total_b_fs", "total_b_fs", 150, 0, 3000, 51, 0, 1020);

TH2D *bmulti_scan_total_frac_fs = new TH2D("total_b_frac_fs", "total_b_frac_fs", 150, 0, 3000, 51, 0, 1020);


_file0->GetObject("fullselection_cuts_375_475/b-multi_scan_0;1", bmulti_scan_fs[0]);
_file0->GetObject("fullselection_cuts_375_475/b-multi_scan_1;1", bmulti_scan_fs[1]);
_file0->GetObject("fullselection_cuts_375_475/b-multi_scan_2;1", bmulti_scan_fs[2]);
_file0->GetObject("fullselection_cuts_375_475/b-multi_scan_3;1", bmulti_scan_fs[3]);


cout << "Filling fractions for FullSelection cuts" << endl;

for(Int_t i=0; i<=3; i++){
	scan_bmulti_frac_fs[i]->Divide(bmulti_scan_fs[i], full_scan_fs);
}

bmulti_scan_total_fs->Add(bmulti_scan_fs[1],bmulti_scan_fs[2]);
bmulti_scan_total_fs->Add(bmulti_scan_fs[3]);

bmulti_scan_total_frac_fs->Divide(bmulti_scan_total_fs, full_scan_fs);



//----------------------------------------------------------------------------------//
//Creat Efficiency Plots

TH2D *scan_eff_NoToPre[4], *scan_eff_PreToFull[4], *scan_eff_NoToFull[4];
TH2D *scan_total_eff_NoToPre, *scan_total_eff_PreToFull, *scan_total_eff_NoToFull;

TH2D *scan_eff_NoToPre[0] = new TH2D("eff_NoToPre_0bs", "eff_NoToPre_0bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_eff_NoToPre[1] = new TH2D("eff_NoToPre_1bs", "eff_NoToPre_1bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_eff_NoToPre[2] = new TH2D("eff_NoToPre_2bs", "eff_NoToPre_2bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_eff_NoToPre[3] = new TH2D("eff_NoToPre_>2bs", "eff_NoToPre_>2bs", 150, 0, 3000, 51, 0, 1020);

TH2D *scan_eff_PreToFull[0] = new TH2D("eff_PreToFull_0bs", "eff_PreToFull_0bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_eff_PreToFull[1] = new TH2D("eff_PreToFull_1bs", "eff_PreToFull_1bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_eff_PreToFull[2] = new TH2D("eff_PreToFull_2bs", "eff_PreToFull_2bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_eff_PreToFull[3] = new TH2D("eff_PreToFull_>2bs", "eff_PreToFull_>2bs", 150, 0, 3000, 51, 0, 1020);

TH2D *scan_eff_NoToFull[0] = new TH2D("eff_NoToFull_0bs", "eff_NoToFull_0bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_eff_NoToFull[1] = new TH2D("eff_NoToFull_1bs", "eff_NoToFull_1bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_eff_NoToFull[2] = new TH2D("eff_NoToFull_2bs", "eff_NoToFull_2bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_eff_NoToFull[3] = new TH2D("eff_NoToFull_>2bs", "eff_NoToFull_>2bs", 150, 0, 3000, 51, 0, 1020);

TH2D *scan_total_eff_NoToPre = new TH2D("eff_NoToPre_total", "eff_NoToPre_total", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_total_eff_PreToFull = new TH2D("eff_PreToFull_total", "eff_PreToFull_total", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_total_eff_NoToFull = new TH2D("eff_NoToFull_total", "eff_NoToFull_total", 150, 0, 3000, 51, 0, 1020);

for(Int_t i=0; i<=3; i++){
	scan_eff_NoToPre[i]->Divide(bmulti_scan_ps[i], bmulti_scan_bf[i]);
	scan_eff_PreToFull[i]->Divide(bmulti_scan_fs[i], bmulti_scan_ps[i]);
	scan_eff_NoToFull[i]->Divide(bmulti_scan_fs[i], bmulti_scan_bf[i]);
}

scan_total_eff_NoToPre->Divide(bmulti_scan_total_ps, bmulti_scan_total_bf);
scan_total_eff_PreToFull->Divide(bmulti_scan_total_fs, bmulti_scan_total_ps);
scan_total_eff_NoToFull->Divide(bmulti_scan_total_fs, bmulti_scan_total_bf);

//----------------------------------------------------------------------------------//
// Add in some restrictions on z-axes here

scan_total_eff_NoToFull->GetZaxis()->SetRangeUser(0,0.2);
scan_total_eff_PreToFull->GetZaxis()->SetRangeUser(0,0.45);
scan_total_eff_NoToPre->GetZaxis()->SetRangeUser(0,0.7);

scan_eff_NoToFull[0]->GetZaxis()->SetRangeUser(0,0.2);
scan_eff_NoToFull[1]->GetZaxis()->SetRangeUser(0,0.7);
scan_eff_NoToFull[2]->GetZaxis()->SetRangeUser(0,0.3);
scan_eff_NoToFull[3]->GetZaxis()->SetRangeUser(0,0.3);

scan_eff_NoToPre[0]->GetZaxis()->SetRangeUser(0,0.6);
scan_eff_NoToPre[2]->GetZaxis()->SetRangeUser(0,0.6);

scan_eff_PreToFull[0]->GetZaxis()->SetRangeUser(0,0.5);
scan_eff_PreToFull[2]->GetZaxis()->SetRangeUser(0,0.45);
scan_eff_PreToFull[3]->GetZaxis()->SetRangeUser(0,0.4);

scan_eff_NoToFull[0]->GetZaxis()->SetRangeUser(0,0.2);
scan_eff_NoToFull[1]->GetZaxis()->SetRangeUser(0,0.7);
scan_eff_NoToFull[2]->GetZaxis()->SetRangeUser(0,0.3);
scan_eff_NoToFull[3]->GetZaxis()->SetRangeUser(0,0.3);

scan_bmulti_frac_bf[1]->GetZaxis()->SetRangeUser(0,0.0025);
scan_bmulti_frac_ps[1]->GetZaxis()->SetRangeUser(0,0.0025);
scan_bmulti_frac_fs[1]->GetZaxis()->SetRangeUser(0,0.0025);

scan_bmulti_frac_bf[3]->GetZaxis()->SetRangeUser(0,1);
scan_bmulti_frac_ps[3]->GetZaxis()->SetRangeUser(0,1);
scan_bmulti_frac_fs[3]->GetZaxis()->SetRangeUser(0,1);

//----------------------------------------------------------------------------------//
cout << "Writing and closing " << histFileName << endl;

_file0->Write();
_file0->Close();

gROOT->ProcessLine(".q");
}
