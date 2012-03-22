#include "TH2.h"
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPaletteAxis.h"
#include "TStyle.h"
#include "TObject.h"
#include "TGaxis.h"
#include <iostream>
#include <sstream>

void GetHistos(int lower, int upper, TString inFile){

	TFile *_file0 = TFile::Open(inFile, "UPDATE");
	
	std::ostringstream outFile, outDir;
	
	outFile << "analysis_output.root";
	if (upper!=975){outDir << "ANA_" << lower << "-" << upper;}
	else {outDir << "ANA_" << lower;}
	
	TFile *_file1 = new TFile(outFile.str().c_str(), "UPDATE");
	
	_file1->mkdir(outDir.str().c_str());
	_file1->cd(outDir.str().c_str());


//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//
	// HISTO DEFINITIONS
	TH2D *bmulti_bf[4], *bmulti_ps[4], *bmulti_fs[4];
	TH2D *scan_bf, *scan_ps, *scan_fs;
	TH2D *frac_bf[5], *frac_ps[5], *frac_fs[5];
	TH2D *eff_bfTops[5], *eff_psTofs[5], *eff_bfTofs[5];
	
	TH2D *bmulti_bf_total = new TH2D("bmulti_bf_total", "bmulti_bf_total", 150, 0, 3000, 51, 0, 1020);
	TH2D *bmulti_ps_total = new TH2D("bmulti_ps_total", "bmulti_ps_total", 150, 0, 3000, 51, 0, 1020);
	TH2D *bmulti_fs_total = new TH2D("bmulti_fs_total", "bmulti_fs_total", 150, 0, 3000, 51, 0, 1020);

	
// fraction plots
	for(int i=0;i<=3;i++){
		std::ostringstream bfTitle, psTitle, fsTitle;
		bfTitle << "frac_bf_" << i;
		if (upper!=975){
			psTitle << "frac_ps_" << lower << "_" << upper << "_" << i;
			fsTitle << "frac_fs_" << lower << "_" << upper << "_" << i;
			}
		else{
			psTitle << "frac_ps_" << lower << "_" << i;
			fsTitle << "frac_fs_" << lower << "_" << i;
			}
		frac_bf[i] = new TH2D(bfTitle.str().c_str(), bfTitle.str().c_str(), 150, 0, 3000, 51, 0, 1020);
		frac_ps[i] = new TH2D(psTitle.str().c_str(), psTitle.str().c_str(), 150, 0, 3000, 51, 0, 1020);
		frac_fs[i] = new TH2D(fsTitle.str().c_str(), fsTitle.str().c_str(), 150, 0, 3000, 51, 0, 1020);
	}
	
	frac_bf[4] = new TH2D("frac_bf_total", "frac_bf_total", 150, 0, 3000, 51, 0, 1020);
	frac_ps[4] = new TH2D("frac_ps_total", "frac_ps_total", 150, 0, 3000, 51, 0, 1020);
	frac_fs[4] = new TH2D("frac_fs_total", "frac_fs_total", 150, 0, 3000, 51, 0, 1020);
	
// efficiency plots
	for(int i=0;i<=3;i++){
		std::ostringstream bfTopsTitle, psTofsTitle, bfTofsTitle;
		bfTopsTitle << "eff_bfTops_" << i;
		psTofsTitle << "eff_psTofs_" << i;
		bfTofsTitle << "eff_bfTofs_" << i;
		eff_bfTops[i] = new TH2D(bfTopsTitle.str().c_str(), bfTopsTitle.str().c_str(), 150, 0, 3000, 51, 0, 1020);
		eff_psTofs[i] = new TH2D(psTofsTitle.str().c_str(), psTofsTitle.str().c_str(), 150, 0, 3000, 51, 0, 1020);
		eff_bfTofs[i] = new TH2D(bfTofsTitle.str().c_str(), bfTofsTitle.str().c_str(), 150, 0, 3000, 51, 0, 1020);
	}
	
	eff_bfTops[4] = new TH2D("eff_bfTops_total", "eff_bfTops_total", 150, 0, 3000, 51, 0, 1020);
	eff_psTofs[4] = new TH2D("eff_psTofs_total", "eff_psTofs_total", 150, 0, 3000, 51, 0, 1020);
	eff_bfTofs[4] = new TH2D("eff_bfTofs_total", "eff_bfTofs_total", 150, 0, 3000, 51, 0, 1020);


//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//
	// GET RAW HISTOGRAMS
	std::ostringstream bfdir, psdir, fsdir;
	
	bfdir << "before_cuts";
	if (upper!=975){
		psdir << "preselection_cuts_" << lower << "_" << upper;
		fsdir << "fullselection_cuts_" << lower << "_" << upper;
		}
	else{
		psdir << "preselection_cuts_" << lower;
		fsdir << "fullselection_cuts_" << lower;	
		}
	
	for(int i = 0; i<=3; i++){
		std::ostringstream bfhist, pshist, fshist;
		bfhist << bfdir.str().c_str() << "/b-multi_scan_" << i << ";1";
		pshist << psdir.str().c_str() << "/b-multi_scan_" << i << ";1";
		fshist << fsdir.str().c_str() << "/b-multi_scan_" << i << ";1";
		
		_file0->GetObject(bfhist.str().c_str(),bmulti_bf[i]);
		_file0->GetObject(pshist.str().c_str(),bmulti_ps[i]);
		_file0->GetObject(fshist.str().c_str(),bmulti_fs[i]);
		
	}
	
	bfdir << "/mSUGRA_Scan_Plane;1";
	psdir << "/mSUGRA_Scan_Plane;1";
	fsdir << "/mSUGRA_Scan_Plane;1";
	
	_file0->GetObject(bfdir.str().c_str(),scan_bf);
	_file0->GetObject(psdir.str().c_str(),scan_ps);
	_file0->GetObject(fsdir.str().c_str(),scan_fs);
	
	bmulti_bf_total->Add(bmulti_bf[1], bmulti_bf[2]);
	bmulti_bf_total->Add(bmulti_bf[3]);
	bmulti_ps_total->Add(bmulti_ps[1], bmulti_ps[2]);
	bmulti_ps_total->Add(bmulti_ps[3]);
	bmulti_fs_total->Add(bmulti_fs[1], bmulti_fs[2]);
	bmulti_fs_total->Add(bmulti_fs[3]);
		
		
		
//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//
	//DO ANALYSIS
		//FILL FRACTIONS
	
	for(int k = 0; k<=3; k++){
		frac_bf[k]->Divide(bmulti_bf[k],scan_bf);
		frac_ps[k]->Divide(bmulti_ps[k],scan_ps);
		frac_fs[k]->Divide(bmulti_fs[k],scan_fs);
	}
	frac_bf[4]->Divide(bmulti_bf_total,scan_bf);
	frac_ps[4]->Divide(bmulti_ps_total,scan_ps);
	frac_fs[4]->Divide(bmulti_fs_total,scan_fs);
	
		//FILL EFFICIENCY PLOTS
	for(int j = 0; j<=3; j++){
		eff_bfTops[j]->Divide(bmulti_ps[j], bmulti_bf[j]);
		eff_psTofs[j]->Divide(bmulti_fs[j], bmulti_ps[j]);
		eff_bfTofs[j]->Divide(bmulti_fs[j], bmulti_bf[j]);
	}
	eff_bfTops[4]->Divide(bmulti_ps_total, bmulti_bf_total);
	eff_psTofs[4]->Divide(bmulti_fs_total, bmulti_ps_total);
	eff_bfTofs[4]->Divide(bmulti_fs_total, bmulti_bf_total);
//----------------------------------------------------------------------------------//	
//----------------------------------------------------------------------------------//
	//WRITE AND CLOSE FILES	
	_file1->Write();
	_file1->Close();
	_file0->Close();
}

//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//


void DrawHistos(int lower, int upper){

	TString inFile = "analysis_output.root";
	TFile *_file2 = TFile::Open(inFile);
	
	std::ostringstream inDir;
	
	if (upper!=975){inDir << "ANA_" << lower << "-" << upper;}
	else {inDir << "ANA_" << lower;}
	
//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//	
	// DO SOME STYLE STUFF
	
	gStyle->SetOptStat(0);

//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//
	// GET ALL HISTOS

	TH2D *frac_bf[5], *frac_ps[5], *frac_fs[5];
	TH2D *eff_bfTops[5], *eff_psTofs[5], *eff_bfTofs[5];
	
// fraction plots
	for(int i=0;i<=3;i++){
		std::ostringstream bfTitle, psTitle, fsTitle;
		bfTitle << inDir.str().c_str() << "/frac_bf_" << i << ";1";
		if (upper!=975){
			psTitle << inDir.str().c_str() << "/frac_ps_" << lower << "_" << upper << "_" << i << ";1";
			fsTitle << inDir.str().c_str() << "/frac_fs_" << lower << "_" << upper << "_" << i << ";1";
			}
		else{
			psTitle << inDir.str().c_str() << "/frac_ps_" << lower << "_" << i << ";1";
			fsTitle << inDir.str().c_str() << "/frac_fs_" << lower << "_" << i << ";1";
			}
		
		_file2->GetObject(bfTitle.str().c_str(), frac_bf[i]);
		_file2->GetObject(psTitle.str().c_str(), frac_ps[i]);
		_file2->GetObject(fsTitle.str().c_str(), frac_fs[i]);
	}

	std::ostringstream bfTitle_total, psTitle_total, fsTitle_total;
	bfTitle_total << inDir.str().c_str() << "/frac_bf_total;1";
	psTitle_total << inDir.str().c_str() << "/frac_ps_total;1";
	fsTitle_total << inDir.str().c_str() << "/frac_fs_total;1";
	
	_file2->GetObject(bfTitle_total.str().c_str(), frac_bf[4]);
	_file2->GetObject(psTitle_total.str().c_str(), frac_ps[4]);
	_file2->GetObject(fsTitle_total.str().c_str(), frac_fs[4]);
	
// efficiency plots
	for(int i=0;i<=3;i++){
		std::ostringstream bfTopsTitle, psTofsTitle, bfTofsTitle;
		bfTopsTitle << inDir.str().c_str() << "/eff_bfTops_" << i << ";1";
		psTofsTitle << inDir.str().c_str() << "/eff_psTofs_" << i << ";1";
		bfTofsTitle << inDir.str().c_str() << "/eff_bfTofs_" << i << ";1";

	_file2->GetObject(bfTopsTitle.str().c_str(), eff_bfTops[i]);
	_file2->GetObject(psTofsTitle.str().c_str(), eff_psTofs[i]);
	_file2->GetObject(bfTofsTitle.str().c_str(), eff_bfTofs[i]);

	}

	std::ostringstream bfTops_total, psTofs_total, bfTofs_total;
	bfTops_total << inDir.str().c_str() << "/eff_bfTops_total;1";
	psTofs_total << inDir.str().c_str() << "/eff_psTofs_total;1";
	bfTofs_total << inDir.str().c_str() << "/eff_bfTofs_total;1";
	
	_file2->GetObject(bfTops_total.str().c_str(), eff_bfTops[4]);
	_file2->GetObject(psTofs_total.str().c_str(), eff_psTofs[4]);
	_file2->GetObject(bfTofs_total.str().c_str(), eff_bfTofs[4]);	
	
//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//
	std::ostringstream outpdf1, outpdf2, outpdf3;
	
	outpdf1 << inDir.str().c_str() << ".pdf(";
	outpdf2 << inDir.str().c_str() << ".pdf";
	outpdf3 << inDir.str().c_str() << ".pdf)";
	
//	frac_bf[1]->Draw("COLZ");
//	TPaletteAxis *palette = (TPaletteAxis*)frac_bf[1]->GetListOfFunctions()->FindObject("palette");
//	palette->SetLabelOffset(-0.015);
//	//frac_bf[1]->Draw("COLZ");
	
	TCanvas c1("c1");
	c1.Print(outpdf1.str().c_str());
	for(int z=0; z<=4; z++){
		frac_bf[z]->Draw("COLZ");
//		if (z==1){
//			   TPaletteAxis *palette = (TPaletteAxis*)frac_bf[z]->GetListOfFunctions()->FindObject("palette");
//			   palette->SetLabelOffset(-0.015);
//			   frac_bf[z]->Draw("COLZ");
//			   }
		c1.Print(outpdf2.str().c_str());
		frac_ps[z]->Draw("COLZ");
//		if (z==1){
//			   TPaletteAxis *palette = (TPaletteAxis*)frac_ps[z]->GetListOfFunctions()->FindObject("palette");
//			   palette->SetLabelOffset(-0.015);
//			   frac_ps[z]->Draw("COLZ");
//			   }
		c1.Print(outpdf2.str().c_str());
		frac_fs[z]->Draw("COLZ");
//		if (z==1){
//			   TPaletteAxis *palette = (TPaletteAxis*)frac_fs[z]->GetListOfFunctions()->FindObject("palette");
//			   palette->SetLabelOffset(-0.015);
//			   frac_fs[z]->Draw("COLZ");
//			   }
		c1.Print(outpdf2.str().c_str());
		eff_bfTops[z]->Draw("COLZ");
		c1.Print(outpdf2.str().c_str());
		eff_psTofs[z]->Draw("COLZ");
		c1.Print(outpdf2.str().c_str());
		eff_bfTofs[z]->Draw("COLZ");
		c1.Print(outpdf2.str().c_str());
	}
	c1.Print(outpdf3.str().c_str());
}

//----------------------------------------------------------------------------------//	
//----------------------------------------------------------------------------------//	
//----------------------------------------------------------------------------------//

void DrawAllHistos(){
	DrawHistos(275,325);
	DrawHistos(325,375);
	for(Int_t i=0; i<=5; i++){
		Int_t lower = 375+i*100;
		Int_t upper = lower+100;
		DrawHistos(lower, upper);
		}
}

//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//

void RunAnalysis(int mode=0){

	TString inFile50 = "../AK5Calo_mSUGRA_m0_220to3000_m12_100to1000_tanb_10andA0_0_7TeV_50_all.root";
	TString inFile43 = "../AK5Calo_mSUGRA_m0_220to3000_m12_100to1000_tanb_10andA0_0_7TeV_43_all.root";
	TString inFile37 = "../AK5Calo_mSUGRA_m0_220to3000_m12_100to1000_tanb_10andA0_0_7TeV_37_all.root";

	if (mode == 50){
		for(Int_t i=0; i<=5; i++){
			Int_t lower = 375+i*100;
			Int_t upper = lower+100;
			GetHistos(lower, upper, inFile50);
			}
		}
	else if (mode==43){ GetHistos(325, 375, inFile43);}
	else if (mode==37){ GetHistos(275, 325, inFile37);}
	else if (mode==0){
		GetHistos(275, 325, inFile37);
		GetHistos(325, 375, inFile43);
		for(Int_t i=0; i<=5; i++){
			Int_t lower = 375+i*100;
			Int_t upper = lower+100;
			GetHistos(lower, upper, inFile50);
			}
		}
	else { std::cout << "Please enter either 37, 43 or 50" << std::endl;}

}
