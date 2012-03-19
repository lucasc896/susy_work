{
TString histFileName = "mSUGRA_m0_220to3000_m12_100to1000_tanb_10andA0_0_7TeV_all.root";

TFile *_file0 = TFile::Open(histFileName, "UPDATE");
_file0->cd("before_cuts_b-multiplicity");

TH2D *full_scan, *b_multi_scan[4], *scan_bmulti_frac_before[4];
TH2D *scan_bmulti_frac_before[0] = new TH2D("0bs", "0bs", 150, 0, 3000, 50, 0, 1000);
TH2D *scan_bmulti_frac_before[1] = new TH2D("1bs", "1bs", 150, 0, 3000, 50, 0, 1000);
TH2D *scan_bmulti_frac_before[2] = new TH2D("2bs", "2bs", 150, 0, 3000, 50, 0, 1000);
TH2D *scan_bmulti_frac_before[3] = new TH2D("NEW >2bs", "NEW >2bs", 150, 0, 3000, 50, 0, 1000);

_file0->GetObject("before_cuts_b-multiplicity/mSUGRA_Scan_Plane;1", full_scan);

_file0->GetObject("before_cuts_b-multiplicity/mSUGRA_Scan_Plane_b-quark_Multiplicity_2;1", b_multi_scan[2]);
_file0->GetObject("before_cuts_b-multiplicity/mSUGRA_Scan_Plane_b-quark_Multiplicity_3;1", b_multi_scan[3]);

TH2D *subtract_temp = new TH2D("subtract", "subtract", 150, 0, 3000, 50, 0, 1000);

subtract_temp->Add(b_multi_scan[3], b_multi_scan[2], 1, -1);
scan_bmulti_frac_before[3]->Divide(subtract_temp, full_scan);

std::cout << "Writing 'before' plots..." << std::endl;
_file0->Write();
_file0->Close();

//-----------------------//
// Repeat for after cuts //
//-----------------------//

TFile *_file1 = TFile::Open(histFileName, "UPDATE");
_file1->cd("after_cuts_b-multiplicity");

TH2D *full_scan, *b_multi_scan[4], *scan_bmulti_frac_after[4];
TH2D *scan_bmulti_frac_after[0] = new TH2D("0bs", "0bs", 150, 0, 3000, 50, 0, 1000);
TH2D *scan_bmulti_frac_after[1] = new TH2D("1bs", "1bs", 150, 0, 3000, 50, 0, 1000);
TH2D *scan_bmulti_frac_after[2] = new TH2D("2bs", "2bs", 150, 0, 3000, 50, 0, 1000);
TH2D *scan_bmulti_frac_after[3] = new TH2D(">2bs", ">2bs", 150, 0, 3000, 50, 0, 1000);

_file1->GetObject("after_cuts_b-multiplicity/mSUGRA_Scan_Plane;1", full_scan);
_file1->GetObject("after_cuts_b-multiplicity/mSUGRA_Scan_Plane_b-quark_Multiplicity_2;1", b_multi_scan[2]);
_file1->GetObject("after_cuts_b-multiplicity/mSUGRA_Scan_Plane_b-quark_Multiplicity_3;1", b_multi_scan[3]);

TH2D *subtract_temp1 = new TH2D("subtract1", "subtract1", 150, 0, 3000, 50, 0, 1000);

subtract_temp1->Add(b_multi_scan[3], b_multi_scan[2], 1, -1);
scan_bmulti_frac_after[3]->Divide(subtract_temp1, full_scan);

std::cout << "Writing 'after' plots..." << std::endl;

_file1->Write();
_file1->Close();

//close all files
}