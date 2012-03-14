{
TFile *_file0 = TFile::Open("AK5Calo_test_pset.root", "UPDATE");
_file0->cd("before_cuts_b-multiplicity");

TH2D *full_scan, *b_multi_scan[4], *scan_bmulti_frac_before[4];
TH2D *scan_bmulti_frac_before[0] = new TH2D("0bs", "0bs", 20, 0, 3000, 20, 0, 1000);
TH2D *scan_bmulti_frac_before[1] = new TH2D("1bs", "1bs", 20, 0, 3000, 20, 0, 1000);
TH2D *scan_bmulti_frac_before[2] = new TH2D("2bs", "2bs", 20, 0, 3000, 20, 0, 1000);
TH2D *scan_bmulti_frac_before[3] = new TH2D(">2bs", ">2bs", 20, 0, 3000, 20, 0, 1000);

_file0->GetObject("before_cuts_b-multiplicity/mSUGRA_Scan_Plane;1", full_scan);
_file0->GetObject("before_cuts_b-multiplicity/mSUGRA_Scan_Plane_b-quark_Multiplicity_0;1", b_multi_scan[0]);
_file0->GetObject("before_cuts_b-multiplicity/mSUGRA_Scan_Plane_b-quark_Multiplicity_1;1", b_multi_scan[1]);
_file0->GetObject("before_cuts_b-multiplicity/mSUGRA_Scan_Plane_b-quark_Multiplicity_2;1", b_multi_scan[2]);
_file0->GetObject("before_cuts_b-multiplicity/mSUGRA_Scan_Plane_b-quark_Multiplicity_3;1", b_multi_scan[3]);

for(Int_t i=0; i<=3; i++){
	scan_bmulti_frac_before[i]->Divide(b_multi_scan[i], full_scan);
}
_file0->Write();
_file0->Close();

//-----------------------//
// Repeat for after cuts //
//-----------------------//


TFile *_file1 = TFile::Open("AK5Calo_test_pset.root", "UPDATE");
_file0->cd("after_cuts_b-multiplicity");


//make a new directory in _file1 for after cuts
//write all of the divided plots to this directory

//close all files
}