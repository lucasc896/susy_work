{

//NEED TO KEEP MAKING PT CUT CHANGES

TString histFileName = "AK5Calo_test_pset.root";

TFile *_file0 = TFile::Open(histFileName, "UPDATE");

TH2D *full_scan_bf, *scan_bmulti_frac_0gev_bf[4], *bmulti_scan_total_0gev_bf;
TH2D *bmulti_scan_0gev_bf[4];

TH2D *scan_bmulti_frac_0gev_bf[0] = new TH2D("bf_frac_0gev_0bs", "bf_frac_0gev_0bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_0gev_bf[1] = new TH2D("bf_frac_0gev_1bs", "bf_frac_0gev_1bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_0gev_bf[2] = new TH2D("bf_frac_0gev_2bs", "bf_frac_0gev_2bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_0gev_bf[3] = new TH2D("bf_frac_0gev_>2bs", "bf_frac_0gev_>2bs", 150, 0, 3000, 51, 0, 1020);

TH2D *bmulti_scan_total_0gev_bf = new TH2D("total_b_0gev_bf", "total_b_0gev_bf", 150, 0, 3000, 51, 0, 1020);
TH2D *bmulti_scan_total_frac_0gev_bf = new TH2D("total_b_frac_0gev_bf", "total_b_frac_0gev_bf", 150, 0, 3000, 51, 0, 1020);

_file0->GetObject("before_cuts/mSUGRA_Scan_Plane;1", full_scan_bf);
_file0->GetObject("before_cuts/mSUGRA_b-quark_multi-0_gev_pt_cut_0;1", bmulti_scan_0gev_bf[0]);
_file0->GetObject("before_cuts/mSUGRA_b-quark_multi-0_gev_pt_cut_1;1", bmulti_scan_0gev_bf[1]);
_file0->GetObject("before_cuts/mSUGRA_b-quark_multi-0_gev_pt_cut_2;1", bmulti_scan_0gev_bf[2]);
_file0->GetObject("before_cuts/mSUGRA_b-quark_multi-0_gev_pt_cut_3;1", bmulti_scan_0gev_bf[3]);

bmulti_scan_total_0gev_bf->Add(bmulti_scan_0gev_bf[1],bmulti_scan_0gev_bf[2]);
bmulti_scan_total_0gev_bf->Add(bmulti_scan_0gev_bf[3]);

cout << "Filling fractions for before cuts" << endl;

for(Int_t i=0; i<=3; i++){
	scan_bmulti_frac_0gev_bf[i]->Divide(bmulti_scan_0gev_bf[i], full_scan_bf);
}

bmulti_scan_total_frac_0gev_bf->Divide(bmulti_scan_total_0gev_bf, full_scan_bf);

///////////////////////////////////////////////////
//-----------------------//
// Repeat for af cuts    //
//-----------------------//
///////////////////////////////////////////////////

TH2D  *full_scan_fs, *scan_bmulti_frac_0gev_fs[4], *scan_bmulti_0gev_eff[4];
TH2D  *bmulti_scan_total_0gev_fs, *scan_bmulti_total_0gev_eff;
TH2D  *bmulti_scan_0gev_fs[4];

TH2D *scan_bmulti_frac_0gev_fs[0] = new TH2D("fs_frac_0gev_0bs", "fs_frac_0gev_0bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_0gev_fs[1] = new TH2D("fs_frac_0gev_1bs", "fs_frac_0gev_1bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_0gev_fs[2] = new TH2D("fs_frac_0gev_2bs", "fs_frac_0gev_2bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_frac_0gev_fs[3] = new TH2D("fs_frac_0gev_>2bs", "fs_frac_0gev_>2bs", 150, 0, 3000, 51, 0, 1020);

TH2D *bmulti_scan_total_0gev_fs = new TH2D("total_b_0gev_fs", "total_b_0gev_fs", 150, 0, 3000, 51, 0, 1020);

TH2D *scan_bmulti_0gev_eff[0] = new TH2D("eff_0gev_0bs", "eff_0gev_0bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_0gev_eff[1] = new TH2D("eff_0gev_1bs", "eff_0gev_1bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_0gev_eff[2] = new TH2D("eff_0gev_2bs", "eff_0gev_2bs", 150, 0, 3000, 51, 0, 1020);
TH2D *scan_bmulti_0gev_eff[3] = new TH2D("eff_0gev_>2bs", "eff_0gev_>2bs", 150, 0, 3000, 51, 0, 1020);

TH2D *scan_bmulti_total_0gev_eff = new TH2D("total_0gev_eff", "total_0gev_eff", 150, 0, 3000, 51, 0, 1020);
TH2D *bmulti_scan_total_frac_0gev_fs = new TH2D("total_b_frac_0gev_fs", "total_b_frac_0gev_fs", 150, 0, 3000, 51, 0, 1020);

_file0->GetObject("fullselection_cuts/mSUGRA_Scan_Plane;1", full_scan_fs);
_file0->GetObject("fullselection_cuts/mSUGRA_b-quark_multi-0_gev_pt_cut_0;1", bmulti_scan_0gev_fs[0]);
_file0->GetObject("fullselection_cuts/mSUGRA_b-quark_multi-0_gev_pt_cut_1;1", bmulti_scan_0gev_fs[1]);
_file0->GetObject("fullselection_cuts/mSUGRA_b-quark_multi-0_gev_pt_cut_2;1", bmulti_scan_0gev_fs[2]);
_file0->GetObject("fullselection_cuts/mSUGRA_b-quark_multi-0_gev_pt_cut_3;1", bmulti_scan_0gev_fs[3]);


cout << "Filling fractions for after cuts" << endl;

for(Int_t i=0; i<=3; i++){
	scan_bmulti_frac_0gev_fs[i]->Divide(bmulti_scan_0gev_fs[i], full_scan_fs);
	scan_bmulti_0gev_eff[i]->Divide(bmulti_scan_0gev_fs[i], bmulti_scan_0gev_fs[i]);
}

bmulti_scan_total_0gev_fs->Add(bmulti_scan_0gev_fs[1],bmulti_scan_0gev_fs[2]);
bmulti_scan_total_0gev_fs->Add(bmulti_scan_0gev_fs[3]);

bmulti_scan_total_frac_0gev_fs->Divide(bmulti_scan_total_0gev_fs, full_scan_fs);

scan_bmulti_total_0gev_eff->Divide(bmulti_scan_total_0gev_fs, bmulti_scan_total_0gev_bf);
scan_bmulti_total_0gev_eff->GetZaxis()->SetRangeUser(0,0.2);

cout << "Writing and closing " << histFileName << endl;

_file0->Write();
_file0->Close();

gROOT->ProcessLine(".q");
}
