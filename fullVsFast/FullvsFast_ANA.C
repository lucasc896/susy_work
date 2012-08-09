#include "FullvsFast_ANA.h"
#include "math.h"

void fullVsFast::BookHistos(){

	nBJets1DHist 	= new TH1D("BJet Multiplicity", "BJet Multiplicity", 16, 0, 16);
	nJets1DHist 	= new TH1D("Jet Multiplicity", "Jet Multiplicity", 16, 0, 16);

}

/*TH1D* fullVsFast::getBJetMultiHist(TFile* inFile, std::vector<TString> vHTBins, float scaleF){
	//want to get the plots nbjet_CommJetgeq2_h_<N>;1

	TCanvas c1;
	std::vector<TFile*> vInFiles;
	std::vector<TString> hNames;

	playHist2D factor=playHist2D();


	vInFiles.push_back(inFile);

	//load histograms into vector
	for(int i=1;i<17;i++){
		std::ostringstream inHistName;
		inHistName << "nbjet_CommJetgeq2_h_" << i <<";1";
		hNames.push_back(inHistName.str().c_str());
	}

	//nBJets1DHist->Clear();

	//sum every nbjets plot
	for(int i=0; i<16; i++){
		nBJets2DHist[i] = factor.addHistForDiffFoldersAndFiles2D(vInFiles,vHTBins, hNames.at(i));
		TH1D* h = nBJets2DHist[i]->ProjectionX();
		nBJets1DHist->Add(h);
	}

	nBJets1DHist->Scale(scaleF);

	return nBJets1DHist;

}*/

TH1D* fullVsFast::getBJetMultiHist(TFile* inFile, std::vector<TString> vHTBins, std::vector<TH2D*> h2D, TH1D* h1D, float scaleF){
	//want to get the plots nbjet_CommJetgeq2_h_<N>;1

	TCanvas c1;
	std::vector<TFile*> vInFiles;
	std::vector<TString> hNames;

	playHist2D factor=playHist2D();


	vInFiles.push_back(inFile);

	//load histograms into vector
	for(int i=1;i<17;i++){
		std::ostringstream inHistName;
		inHistName << "nbjet_CommJetgeq2_h_" << i <<";1";
		hNames.push_back(inHistName.str().c_str());
	}

	//nBJets1DHist->Clear();

	//sum every nbjets plot
	for(int i=0; i<16; i++){
		h2D.push_back( factor.addHistForDiffFoldersAndFiles2D(vInFiles,vHTBins, hNames.at(i)) );
		TH1D* h = h2D.at(i)->ProjectionX();
		h1D->Add(h);
	}

	h1D->Sumw2();
	h1D->Scale(scaleF);

	return h1D;

}

TH1D* fullVsFast::getJetMultiHist(TFile* inFile, std::vector<TString> vHTBins, std::vector<TH2D*> h2D, TH1D* h1D, float scaleF){
	//want to get the plots njet_CommJetgeq2_h_<N>;1

	TCanvas c1;
	std::vector<TFile*> vInFiles;
	std::vector<TString> hNames;

	playHist2D factor=playHist2D();


	vInFiles.push_back(inFile);

	//load histograms into vector
	for(int i=1;i<17;i++){
		std::ostringstream inHistName;
		inHistName << "njet_CommJetgeq2_h_" << i <<";1";
		hNames.push_back(inHistName.str().c_str());
	}

	nJets1DHist->Reset();

	//sum every njets plot
	for(int i=0; i<16; i++){
		nJets2DHist[i] = factor.addHistForDiffFoldersAndFiles2D(vInFiles,vHTBins, hNames.at(i));
		TH1D* h1 = nJets2DHist[i]->ProjectionX();
		nJets1DHist->Add(h1);
	}

	nJets1DHist->Sumw2();
	nJets1DHist->Scale(scaleF);

	return nJets1DHist;

}

TH1D* fullVsFast::getGenericObjHist2D(TFile* inFile, std::vector<TString> vHTBins, TString histName, float scaleF, float normF, float binOffset){

	std::vector<TFile*> vInFiles;
	std::vector<TString> hNames;
	playHist2D factor=playHist2D(); //create playHist2D with default constructor

	vInFiles.push_back(inFile);
	hNames.push_back(histName);

	TH2D* h2D = factor.addHistForDiffFoldersAndFiles2D(vInFiles,vHTBins, hNames.at(0));
	int nxBins = h2D->GetNbinsX();
	
	std::cout << nxBins << std::endl;
	
	TCanvas c1;
	h2D->Draw("colz");
	//c1.Print("test.pdf");

	TH1D *h1D =	h2D->ProjectionX();  //"h1", 2, 5, "e");
	
	h1D->Scale(scaleF);
	
	std::cout << "hey mum" << std::endl;
	
	return h1D;

}

//-------------------------------------------------//

void fullVsFast::runAnalysis(){

	TCanvas *c2 = new TCanvas("c2","example",500,400);
	TString inFileNameFull, inFileNameFast;
	std::vector<TString> vHTBins, vHTBins_lowerStrip, vHTBins_beforeCuts, vHTBins_beforeMHTMET, hNamesNorm, test_names;
	bool printFinalPlots = true;
	playHist1D pHists1D=playHist1D();

//	inFileNameFull = "/Users/cl7359/SUSY/FastvsFullStudy/data_files/final_150512_214900/T1tttt_fullSim_allHTBins.root";
//	inFileNameFast = "/Users/cl7359/SUSY/FastvsFullStudy/data_files/final_150512_214900/T1tttt_fastSim_allHTBins.root";

//	inFileNameFull = "/Users/cl7359/SUSY/FastvsFullStudy/data_files/Zinv400toInf/Zinv_400toinf_fullSim_all_METcompare.root";
//	inFileNameFast = "/Users/cl7359/SUSY/FastvsFullStudy/data_files/Zinv400toInf/Zinv_400toinf_fastSim_all_METcompare.root";

	inFileNameFull = "/Users/cl7359/SUSY/FastvsFullStudy/data_files/T1tttt/T1tttt_fullSim_allBins_METcompare_onePoint.root";
	inFileNameFast = "/Users/cl7359/SUSY/FastvsFullStudy/data_files/T1tttt/T1tttt_fastSim_allBins_METcompare_onePoint.root";

	TFile *inFileFull = TFile::Open(inFileNameFull, "r");
	TFile *inFileFast = TFile::Open(inFileNameFast, "r");

	std::vector<TFile*> vInFilesFast;
	std::vector<TFile*> vInFilesFull;
	
	vInFilesFast.push_back(inFileFast);
	vInFilesFull.push_back(inFileFull);
	
	TString histNormName = "totalEvents_h_all;1";
	
	hNamesNorm.push_back(histNormName);

	BookHistos();

	//fill vectors
	vHTBins.push_back("275-325");
	vHTBins.push_back("325_375");
	vHTBins.push_back("375_475");
	vHTBins.push_back("475_575");
	vHTBins.push_back("575_675");
	vHTBins.push_back("675_775");
	vHTBins.push_back("775_875");
	vHTBins.push_back("875");
	
	vHTBins_lowerStrip.push_back("afterAlphaT275_325");
	vHTBins_lowerStrip.push_back("afterAlphaT325_375");
	vHTBins_lowerStrip.push_back("afterAlphaT375_475");
	vHTBins_lowerStrip.push_back("afterAlphaT475_575");
	vHTBins_lowerStrip.push_back("afterAlphaT575_675");
	vHTBins_lowerStrip.push_back("afterAlphaT675_775");
	vHTBins_lowerStrip.push_back("afterAlphaT775_875");
	vHTBins_lowerStrip.push_back("afterAlphaT875");

	vHTBins_beforeCuts.push_back("beforeCuts_275_325");
	vHTBins_beforeCuts.push_back("beforeCuts_325_375");
	vHTBins_beforeCuts.push_back("beforeCuts_375_475");
	vHTBins_beforeCuts.push_back("beforeCuts_475_575");
	vHTBins_beforeCuts.push_back("beforeCuts_575_675");
	vHTBins_beforeCuts.push_back("beforeCuts_675_775");
	vHTBins_beforeCuts.push_back("beforeCuts_775_875");
	vHTBins_beforeCuts.push_back("beforeCuts_875");

	vHTBins_beforeMHTMET.push_back("beforeMHTMET_275_325");
	vHTBins_beforeMHTMET.push_back("beforeMHTMET_325_375");
	vHTBins_beforeMHTMET.push_back("beforeMHTMET_375_475");
	vHTBins_beforeMHTMET.push_back("beforeMHTMET_475_575");
	vHTBins_beforeMHTMET.push_back("beforeMHTMET_575_675");
	vHTBins_beforeMHTMET.push_back("beforeMHTMET_675_775");
	vHTBins_beforeMHTMET.push_back("beforeMHTMET_775_875");
	vHTBins_beforeMHTMET.push_back("beforeMHTMET_875");

	//calculate scaling factor for full->fast event size
	
	TH1D* fullAllEv = pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, hNamesNorm.at(0) );
	double fullSimEvts = fullAllEv->Integral( 1, fullAllEv->GetNbinsX() );
	
	TH1D* fastAllEv = pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, hNamesNorm.at(0) );
	double fastSimEvts = fastAllEv->Integral( 1, fastAllEv->GetNbinsX() );
	
	std::cout << "Number of fullSim events: " << fullAllEv->Integral(1,fullAllEv->GetNbinsX()) << std::endl;
	std::cout << "Number of fastSim events: " << fastAllEv->Integral(1,fastAllEv->GetNbinsX()) << std::endl;
	
	
	//float fullToFastScale = 3346000./550600.;
	float fullScaleF = 1./fullSimEvts;
	float fastScaleF = 1./fastSimEvts;

	//float fullScaleF = 1.;
	//float fastScaleF = 1.;

	//c2->SetLogy(1);

	TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
    pad1->SetBottomMargin(0.01);
    pad1->Draw();
    pad1->cd();
    pad1->SetLogy();

	test_names.push_back("AlphaT_CommJetgeq2_h_all;1");	

	TH1D aT1;
	aT1.Sumw2(); 
	aT1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(0) );
	aT1.Scale(fullScaleF);
	aT1.SetLineColor(kBlue);
	aT1.Rebin(10);
	aT1.GetXaxis()->SetTitle("#alpha_{T}");
	aT1.GetXaxis()->SetRangeUser(0,2.5);

	TH1D aT2;
	aT2.Sumw2();
	aT2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(0) );
	aT2.Scale(fastScaleF);
	aT2.SetLineColor(kRed);
	aT2.Rebin(10);
	aT2.GetXaxis()->SetRangeUser(0,2.5);

    aT1.DrawCopy("hist");
    aT2.Draw("histsame");
    c2->cd();

    TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
    pad2->SetTopMargin(0.05);
    pad2->SetBottomMargin(0.22);
    pad2->SetGridx(1);
    pad2->SetGridy(1);
    pad2->Draw();
    pad2->cd();

    aT1.SetStats(0);
    aT1.Sumw2();    
    aT1.Divide(&aT2);
    aT1.SetMarkerStyle(7);
    aT1.GetXaxis()->SetTitle("#alpha_{T}");
    aT1.GetYaxis()->SetTitle("Full/Fast");
    aT1.GetYaxis()->SetRangeUser(0,2);
    aT1.SetLabelSize(0.08, "X");
    aT1.SetLabelSize(0.07, "Y");
    aT1.SetTitleSize(0.09, "X");
    aT1.SetTitleSize(0.09, "Y");
    aT1.SetTitleOffset(0.25, "Y");
    aT1.Draw("pe");
    c2->cd();

	if( printFinalPlots ) c2->Print("../results/alphaT_log_ratio.pdf");
	c2->Print("../test.pdf(");

	// ******************************************************** //

	pad1->cd();

	test_names.push_back("bJetMulti_distro_h;1"); // CHECK

	TH1D bJM1;
	bJM1.Sumw2();
	bJM1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(1) );
	bJM1.SetLineColor(kBlue);
	bJM1.GetXaxis()->SetTitle("B-tagged Jet Multiplicity");
	bJM1.GetXaxis()->SetRangeUser(0,10);

	TH1D bJM2;
	bJM2.Sumw2();
	bJM2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(1) );
	bJM2.SetLineColor(kRed);
	bJM2.GetXaxis()->SetRangeUser(0,10);

	bJM1.Scale(fullScaleF);
	bJM2.Scale(fastScaleF);

	bJM1.DrawCopy();
	bJM2.Draw("same");

    c2->cd();
    pad2->cd();

    bJM1.SetStats(0);
    bJM1.Divide(&bJM2);
    bJM1.SetMarkerStyle(7);
    bJM1.GetXaxis()->SetTitle("B-tagged Jet Multiplicity");
    bJM1.GetYaxis()->SetTitle("Full/Fast");
    bJM1.GetYaxis()->SetRangeUser(0,2);
    bJM1.SetLabelSize(0.08, "X");
    bJM1.SetLabelSize(0.07, "Y");
    bJM1.SetTitleSize(0.09, "X");
    bJM1.SetTitleSize(0.09, "Y");
    bJM1.SetTitleOffset(0.25, "Y");
    bJM1.Draw("pe");
    c2->cd();
	
	if( printFinalPlots) c2->Print("../results/bJetMulti_log_ratio.pdf");
	c2->Print("../test.pdf");

	// ******************************************************** //

	pad1->cd();
	test_names.push_back("JetMulti_distro_h;1");
	
	TH1D jM1;
	jM1.Sumw2();
	jM1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(2) );
	jM1.SetLineColor(kBlue);

	TH1D jM2;
	jM2.Sumw2();
	jM2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(2) );
	jM2.SetLineColor(kRed);
	jM2.GetXaxis()->SetTitle("Jet Multiplicity");
	
	jM1.Scale(fullScaleF);
	jM2.Scale(fastScaleF);
	
	jM1.DrawCopy();
	jM2.Draw("SAME");

	c2->cd();
    pad2->cd();	

    jM1.SetStats(0);
    jM1.Divide(&jM2);
    jM1.SetMarkerStyle(7);
    jM1.GetXaxis()->SetTitle("Jet Multiplicity");
    jM1.GetYaxis()->SetTitle("Full/Fast");
    jM1.GetYaxis()->SetRangeUser(0,2);
    jM1.SetLabelSize(0.06, "X");
    jM1.SetLabelSize(0.05, "Y");
    jM1.SetTitleSize(0.09, "X");
    jM1.SetTitleSize(0.09, "Y");
    jM1.SetTitleOffset(0.25, "Y");
    jM1.Draw("p");
    c2->cd();

	//c2->Print("../test.pdf");

    // ******************************************************** //

	pad1->cd();

	test_names.push_back("bjetPt_CommJetgeq2_h__all;1");

	TH1D bJPt1;
	bJPt1.Sumw2();
	bJPt1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(3) );
	bJPt1.Scale(fullScaleF);
	bJPt1.SetLineColor(kBlue);
	bJPt1.GetXaxis()->SetTitle("B-tagged Jet p_{T} (GeV)");


	TH1D bJPt2;
	bJPt2.Sumw2();
	bJPt2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(3) );
	bJPt2.Scale(fastScaleF);
	bJPt2.SetLineColor(kRed);
	
	bJPt1.Rebin(20);
	bJPt2.Rebin(20);
	bJPt1.GetXaxis()->SetRangeUser(0,1300);
	bJPt1.DrawCopy("hist");
	bJPt2.Draw("histSAME");

	c2->cd();
	pad2->cd();

	bJPt1.SetStats(0);
	bJPt1.Divide(&bJPt2);
	bJPt1.Sumw2();
	bJPt1.SetMarkerStyle(7);
	bJPt1.GetXaxis()->SetTitle("BJet p_{T} (GeV)");
	bJPt1.GetYaxis()->SetTitle("Full/Fast");
	bJPt1.GetYaxis()->SetRangeUser(0,2);
	bJPt1.GetXaxis()->SetRangeUser(0,1300);
	bJPt1.SetLabelSize(0.08, "X");
	bJPt1.SetLabelSize(0.07, "Y");
	bJPt1.SetTitleSize(0.09, "X");
	bJPt1.SetTitleSize(0.09, "Y");
	bJPt1.SetTitleOffset(0.25, "Y");
	bJPt1.Draw("p");
	c2->cd();
	

	if( printFinalPlots ) c2->Print("../results/bJetsPt_log_ratio.pdf");
	c2->Print("../test.pdf");

	// ******************************************************** //

	pad1->cd();

	test_names.push_back("bjetEta_CommJetgeq2_h__all;1");

	TH1D bJEta1;
	bJEta1.Sumw2();
	bJEta1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(4) );
	bJEta1.Scale(fullScaleF);
	bJEta1.SetLineColor(kBlue);
	bJEta1.Rebin(2);
	bJEta1.GetXaxis()->SetRangeUser(-5,5);

	TH1D bJEta2;
	bJEta2.Sumw2();
	bJEta2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(4) );
	bJEta2.Scale(fastScaleF);
	bJEta2.SetLineColor(kRed);
	bJEta2.Rebin(2);
	bJEta2.GetXaxis()->SetRangeUser(-5,5);
	bJEta1.DrawCopy("hist");
	bJEta2.Draw("histSAME");

	c2->cd();
	pad2->cd();

	bJEta1.SetStats(0);
	bJEta1.Divide(&bJEta2);
	bJEta1.Sumw2();
	bJEta1.SetMarkerStyle(7);
	bJEta1.GetXaxis()->SetTitle("BJet #eta");
	bJEta1.GetYaxis()->SetTitle("Full/Fast");
	bJEta1.GetXaxis()->SetRangeUser(-5,5);
	bJEta1.GetYaxis()->SetRangeUser(0,2);
	bJEta1.SetLabelSize(0.08, "X");
	bJEta1.SetLabelSize(0.07, "Y");
	bJEta1.SetTitleSize(0.09, "X");
	bJEta1.SetTitleSize(0.09, "Y");
	bJEta1.SetTitleOffset(0.25, "Y");
	bJEta1.Draw("p");
	c2->cd();

	if( printFinalPlots ) c2->Print("../results/bJetsEta_log_ratio.pdf");
	c2->Print("../test.pdf");

	// ******************************************************** //

/*	pad1->cd();

	TH1D bJPhi1 = *getGenericObjHist(inFileFull, vHTBins_beforeCuts_lowerStrip, "bjetPhi_CommJetgeq2_h__all;1", fullScaleF, 6.5/200.);
	bJPhi1.SetLineColor(kBlue);
	bJPhi1.GetXaxis()->SetRangeUser(-0.1,3.5);

	TH1D bJPhi2 = *getGenericObjHist(inFileFast, vHTBins_beforeCuts_lowerStrip, "bjetPhi_CommJetgeq2_h__all;1", fastScaleF, 6.5/200.);
	bJPhi2.SetLineColor(kRed);
	bJPhi2.GetXaxis()->SetRangeUser(-0.1,3.5);
	bJPhi1.DrawCopy("hist");
	bJPhi2.Draw("histSAME");

	c2->cd();
	pad2->cd();

	bJPhi1.SetStats(0);
	bJPhi1.Divide(&bJPhi2);
	bJPhi1.Sumw2();
	bJPhi1.SetMarkerStyle(7);
	bJPhi1.GetXaxis()->SetTitle("BJet #phi");
	bJPhi1.GetYaxis()->SetTitle("Full/Fast");
	bJPhi1.GetYaxis()->SetRangeUser(0,2);
	bJPhi1.SetLabelSize(0.08, "X");
	bJPhi1.SetLabelSize(0.07, "Y");
	bJPhi1.SetTitleSize(0.09, "X");
	bJPhi1.SetTitleSize(0.09, "Y");
	bJPhi1.SetTitleOffset(0.25, "Y");
	bJPhi1.Draw("p");
	c2->cd();

	if( printFinalPlots ) c2->Print("../results/bJetsPhi_log_ratio.pdf");
	//c2->Print("../test.pdf");

	// ******************************************************** //

*/	pad1->cd();
	test_names.push_back("jetPt_CommJetgeq2_h__all;1");
	
	TH1D JPt1;
	JPt1.Sumw2();
	JPt1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(5) );
	JPt1.Scale(fullScaleF);
	JPt1.SetLineColor(kBlue);

	TH1D JPt2;
	JPt2.Sumw2();
	JPt2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(5) );
	JPt2.Scale(fastScaleF);
	JPt2.SetLineColor(kRed);
	JPt1.Sumw2();
	JPt2.Sumw2();
	JPt1.Rebin(20);
	JPt2.Rebin(20);
	JPt1.GetXaxis()->SetRangeUser(0,1400);
	JPt1.DrawCopy("hist");
	JPt2.Draw("histSAME");

	c2->cd();
	pad2->cd();

	JPt1.SetStats(0);
	JPt1.Divide(&JPt2);
	JPt1.Sumw2();
	JPt1.SetMarkerStyle(7);
	JPt1.GetXaxis()->SetTitle("Jet p_{T} (GeV)");
	JPt1.GetYaxis()->SetTitle("Full/Fast");
	JPt1.GetYaxis()->SetRangeUser(0,2);
	JPt1.GetXaxis()->SetRangeUser(0,1400);
	JPt1.SetLabelSize(0.08, "X");
	JPt1.SetLabelSize(0.07, "Y");
	JPt1.SetTitleSize(0.09, "X");
	JPt1.SetTitleSize(0.09, "Y");
	JPt1.SetTitleOffset(0.25, "Y");
	JPt1.Draw("p");
	c2->cd();

	if( printFinalPlots ) c2->Print("../results/jetsPt_log_ratio.pdf");
	c2->Print("../test.pdf");

	// ******************************************************** //

	pad1->cd();
	
	test_names.push_back("jetEta_CommJetgeq2_h__all;1");

	TH1D JEta1;
	JEta1.Sumw2();
	JEta1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(6) );
	JEta1.Scale(fullScaleF);
	JEta1.SetLineColor(kBlue);
	//JEta1.GetXaxis()->SetRangeUser(-5,5);

	TH1D JEta2;
	JEta2.Sumw2();
	JEta2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(6) );
	JEta2.Scale(fastScaleF);
	JEta2.SetLineColor(kRed);
	JEta1.Rebin(2);
	JEta2.Rebin(2);
	JEta1.GetXaxis()->SetRangeUser(-5,5);
	JEta1.DrawCopy("hist");
	JEta2.Draw("histSAME");

	c2->cd();
	pad2->cd();

	JEta1.SetStats(0);
	JEta1.Divide(&JEta2);
	JEta1.Sumw2();
	JEta1.SetMarkerStyle(7);
	JEta1.GetXaxis()->SetTitle("Jet #eta");
	JEta1.GetYaxis()->SetTitle("Full/Fast");
	JEta1.GetXaxis()->SetRangeUser(-5,5);
	JEta1.GetYaxis()->SetRangeUser(0,2);
	JEta1.SetLabelSize(0.08, "X");
	JEta1.SetLabelSize(0.07, "Y");
	JEta1.SetTitleSize(0.09, "X");
	JEta1.SetTitleSize(0.09, "Y");
	JEta1.SetTitleOffset(0.25, "Y");
	JEta1.Draw("p");
	c2->cd();

	if( printFinalPlots ) c2->Print("../results/jetsEta_log_ratio.pdf");
	c2->Print("../test.pdf");
	
	// ******************************************************** //

	pad1->cd();

/*	TH1D JPhi1 = *getGenericObjHist(inFileFull, vHTBins_beforeCuts_lowerStrip, "jetPhi_CommJetgeq2_h__all;1", fullScaleF, 6.5/200.);
	JPhi1.SetLineColor(kBlue);
	JPhi1.GetXaxis()->SetRangeUser(-0.1,3.5);

	TH1D JPhi2 = *getGenericObjHist(inFileFast, vHTBins_beforeCuts_lowerStrip, "jetPhi_CommJetgeq2_h__all;1", fastScaleF, 6.5/200.);
	JPhi2.SetLineColor(kRed);
	JPhi2.GetXaxis()->SetRangeUser(-0.1,3.5);
	JPhi1.DrawCopy("hist");
	JPhi2.Draw("histSAME");

	c2->cd();
	pad2->cd();

	JPhi1.SetStats(0);
	JPhi1.Divide(&JPhi2);
	JPhi1.Sumw2();
	JPhi1.SetMarkerStyle(7);
	JPhi1.GetXaxis()->SetTitle("Jet #phi");
	JPhi1.GetYaxis()->SetTitle("Full/Fast");
	JPhi1.GetYaxis()->SetRangeUser(0,2);
	JPhi1.SetLabelSize(0.08, "X");
	JPhi1.SetLabelSize(0.07, "Y");
	JPhi1.SetTitleSize(0.09, "X");
	JPhi1.SetTitleSize(0.09, "Y");
	JPhi1.SetTitleOffset(0.25, "Y");
	JPhi1.Draw("p");
	c2->cd();

	if( printFinalPlots ) c2->Print("../results/jetsPhi_log_ratio.pdf");
	//c2->Print("../test.pdf");
*/
	// ******************************************************** //

	pad1->cd();

	test_names.push_back("leadJetPt_CommJetgeq2_h__all;1");

	TH1D leadJPt1;
	leadJPt1.Sumw2();
	leadJPt1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(7) );
	leadJPt1.Scale(fullScaleF);
	leadJPt1.SetLineColor(kBlue);
	TH1D leadJPt2;
	leadJPt2.Sumw2();
	
	leadJPt2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(7) );
	leadJPt2.Scale(fastScaleF);
	leadJPt2.SetLineColor(kRed);
	leadJPt1.Rebin(25);
	leadJPt2.Rebin(25);
	leadJPt2.GetXaxis()->SetRangeUser(0,2000);
	leadJPt2.Draw("hist");
	leadJPt1.DrawCopy("histSAME");
	
	c2->cd();
	pad2->cd();

	leadJPt1.SetStats(0);
	leadJPt1.Divide(&leadJPt2);
	leadJPt1.Sumw2();
	leadJPt1.SetMarkerStyle(7);
	leadJPt1.GetXaxis()->SetTitle("Leading Jet p_{T} (GeV)");
	leadJPt1.GetYaxis()->SetTitle("Full/Fast");
	leadJPt1.GetYaxis()->SetRangeUser(0,2);
	leadJPt1.GetXaxis()->SetRangeUser(0,2000);
	leadJPt1.SetLabelSize(0.08, "X");
	leadJPt1.SetLabelSize(0.07, "Y");
	leadJPt1.SetTitleSize(0.09, "X");
	leadJPt1.SetTitleSize(0.09, "Y");
	leadJPt1.SetTitleOffset(0.25, "Y");
	leadJPt1.Draw("p");
	c2->cd();

	if( printFinalPlots ) c2->Print("../results/leadJetPt_log_ratio.pdf");
	c2->Print("../test.pdf");

	// ******************************************************** //

	pad1->cd();
	test_names.push_back("HT_distro_h;1");

	TH1D HT1;
	HT1.Sumw2();
	HT1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(8) );
	HT1.SetLineColor(kBlue);
	HT1.GetXaxis()->SetRangeUser(0,2500);

	TH1D HT2;
	HT2.Sumw2();
	HT2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(8) );
	HT2.SetLineColor(kRed);
	HT1.Rebin(20);
	HT2.Rebin(20);
	
	HT1.Scale(fullScaleF);
	HT2.Scale(fastScaleF);
	
	HT1.DrawCopy("hist");
	HT2.Draw("histSAME");
	
	pad2->cd();

	HT1.SetStats(0);
	HT1.Divide(&HT2);
	HT1.Sumw2();
	HT1.SetMarkerStyle(7);
	HT1.GetXaxis()->SetTitle("HT (GeV)");
	HT1.GetYaxis()->SetTitle("Full/Fast");
	HT1.GetYaxis()->SetRangeUser(0,2);
	HT1.SetLabelSize(0.08, "X");
	HT1.SetLabelSize(0.07, "Y");
	HT1.SetTitleSize(0.09, "X");
	HT1.SetTitleSize(0.09, "Y");
	HT1.SetTitleOffset(0.25, "Y");
	HT1.Draw("p");
	c2->cd();

	if( printFinalPlots ) c2->Print("../results/HT_log_ratio.pdf");
	c2->Print("../test.pdf");

	// ******************************************************** //

	pad1->cd();
	test_names.push_back("MHT_distro_h;1");

	TH1D MHT1;
	MHT1.Sumw2();
	MHT1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(9) );
	MHT1.SetLineColor(kBlue);

	TH1D MHT2;
	MHT2.Sumw2();
	MHT2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(9) );
	MHT2.SetLineColor(kRed);
	MHT1.Rebin(15);
	MHT2.Rebin(15);
	
	MHT1.Scale(fullScaleF);
	MHT2.Scale(fastScaleF);
	
	MHT1.DrawCopy("hist");
	MHT2.Draw("histSAME");

	c2->cd();
	pad2->cd();

	MHT1.SetStats(0);
	MHT1.Sumw2();	
	MHT1.Divide(&MHT2);
	MHT1.SetMarkerStyle(7);
	MHT1.GetXaxis()->SetTitle("MHT (GeV)");
	MHT1.GetYaxis()->SetTitle("Full/Fast");
	MHT1.GetYaxis()->SetRangeUser(0,2);
	MHT1.SetLabelSize(0.08, "X");
	MHT1.SetLabelSize(0.07, "Y");
	MHT1.SetTitleSize(0.09, "X");
	MHT1.SetTitleSize(0.09, "Y");
	MHT1.SetTitleOffset(0.25, "Y");
	MHT1.Draw("p");
	c2->cd();

	if( printFinalPlots ) c2->Print("../results/MHT_log_ratio.pdf");
	c2->Print("../test.pdf");

	// ******************************************************** //

	//pad1->cd();
	test_names.push_back("MHToverMET_distro_h;1");
/*
	TH1D MHTMET1;
	MHTMET1.Sumw2();
	MHTMET1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(10) );
	MHTMET1.SetLineColor(kBlue);
	MHTMET1.Rebin(10);
	MHTMET1.GetXaxis()->SetRangeUser(0,2.5);

	TH1D MHTMET2;
	MHTMET2.Sumw2();
	MHTMET2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(10) );
	MHTMET2.SetLineColor(kRed);
	MHTMET2.Rebin(10);
	MHTMET2.GetXaxis()->SetRangeUser(0,2.5);
	
	MHTMET1.Scale(fullScaleF);
	MHTMET2.Scale(fastScaleF);
	
	MHTMET1.DrawCopy("hist");
	MHTMET2.Draw("histSAME");

	c2->cd();
	pad2->cd();

	MHTMET1.SetStats(0);
	MHTMET1.Sumw2();
	MHTMET1.Divide(&MHTMET2);
	MHTMET1.SetMarkerStyle(7);
	MHTMET1.GetXaxis()->SetTitle("MHTMET");
	MHTMET1.GetYaxis()->SetTitle("Full/Fast");
	MHTMET1.GetYaxis()->SetRangeUser(0,2);
	MHTMET1.SetLabelSize(0.08, "X");
	MHTMET1.SetLabelSize(0.07, "Y");
	MHTMET1.SetTitleSize(0.09, "X");
	MHTMET1.SetTitleSize(0.09, "Y");
	MHTMET1.SetTitleOffset(0.25, "Y");
	MHTMET1.Draw("p");
	c2->cd();

	if( printFinalPlots ) c2->Print("../results/MHToverMET_log_ratio.pdf");
	c2->Print("../test.pdf");*/

	// ******************************************************** //

	pad1->cd();
	test_names.push_back("MET_CaloMet_distro_h_;1");

	TH1D METCalo1;
	METCalo1.Sumw2();
	METCalo1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(11) );
	METCalo1.SetLineColor(kBlue);
	METCalo1.Rebin(20);
	METCalo1.GetXaxis()->SetRangeUser(0,1500);

	TH1D METCalo2;
	METCalo2.Sumw2();
	METCalo2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(11) );
	METCalo2.SetLineColor(kRed);
	METCalo2.Rebin(20);
	METCalo2.GetXaxis()->SetRangeUser(0,1500);

	METCalo1.Scale(fullScaleF);
	METCalo2.Scale(fastScaleF);

	METCalo1.DrawCopy("hist");
	METCalo2.Draw("histSAME");

	c2->cd();
	pad2->cd();

	METCalo1.SetStats(0);
	METCalo1.Sumw2();
	METCalo1.Divide(&METCalo2);
	METCalo1.SetMarkerStyle(7);
	METCalo1.GetXaxis()->SetTitle("METCalo");
	METCalo1.GetYaxis()->SetTitle("Full/Fast");
	METCalo1.GetYaxis()->SetRangeUser(0,2);
	METCalo1.SetLabelSize(0.08, "X");
	METCalo1.SetLabelSize(0.07, "Y");
	METCalo1.SetTitleSize(0.09, "X");
	METCalo1.SetTitleSize(0.09, "Y");
	METCalo1.SetTitleOffset(0.25, "Y");
	METCalo1.Draw("p");
	c2->cd();

	if( printFinalPlots ) c2->Print("../results/MHToverMET_log_ratio.pdf");
	c2->Print("../test.pdf");


	// ******************************************************** //

	pad1->cd();
	test_names.push_back("MET_typeIPFMet_distro_h_;1");

	TH1D METtypeIPF1;
	METtypeIPF1.Sumw2();
	METtypeIPF1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(12) );
	METtypeIPF1.SetLineColor(kBlue);
	METtypeIPF1.Rebin(20);
	METtypeIPF1.GetXaxis()->SetRangeUser(0,1500);

	TH1D METtypeIPF2;
	METtypeIPF2.Sumw2();
	METtypeIPF2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(12) );
	METtypeIPF2.SetLineColor(kRed);
	METtypeIPF2.Rebin(20);
	METtypeIPF2.GetXaxis()->SetRangeUser(0,1500);

	METtypeIPF1.Scale(fullScaleF);
	METtypeIPF2.Scale(fastScaleF);

	METtypeIPF1.DrawCopy("hist");
	METtypeIPF2.Draw("histSAME");

	c2->cd();
	pad2->cd();

	METtypeIPF1.SetStats(0);
	METtypeIPF1.Sumw2();
	METtypeIPF1.Divide(&METtypeIPF2);
	METtypeIPF1.SetMarkerStyle(7);
	METtypeIPF1.GetXaxis()->SetTitle("METtypeIPF");
	METtypeIPF1.GetYaxis()->SetTitle("Full/Fast");
	METtypeIPF1.GetYaxis()->SetRangeUser(0,2);
	METtypeIPF1.SetLabelSize(0.08, "X");
	METtypeIPF1.SetLabelSize(0.07, "Y");
	METtypeIPF1.SetTitleSize(0.09, "X");
	METtypeIPF1.SetTitleSize(0.09, "Y");
	METtypeIPF1.SetTitleOffset(0.25, "Y");
	METtypeIPF1.Draw("p");
	c2->cd();

	if( printFinalPlots ) c2->Print("../results/MHToverMET_log_ratio.pdf");
	c2->Print("../test.pdf");

	// ******************************************************** //

	pad1->cd();
	test_names.push_back("MHToverMET_CaloMet_distro_h_;1");

	TH1D MHTMETCalo1;
	MHTMETCalo1.Sumw2();
	MHTMETCalo1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(13) );
	MHTMETCalo1.SetLineColor(kBlue);
	MHTMETCalo1.Rebin(10);
	MHTMETCalo1.GetXaxis()->SetRangeUser(0,1500);

	TH1D MHTMETCalo2;
	MHTMETCalo2.Sumw2();
	MHTMETCalo2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(13) );
	MHTMETCalo2.SetLineColor(kRed);
	MHTMETCalo2.Rebin(10);
	MHTMETCalo2.GetXaxis()->SetRangeUser(0,1500);

	MHTMETCalo1.Scale(fullScaleF);
	MHTMETCalo2.Scale(fastScaleF);

	MHTMETCalo1.DrawCopy("hist");
	MHTMETCalo2.Draw("histSAME");

	c2->cd();
	pad2->cd();

	MHTMETCalo1.SetStats(0);
	MHTMETCalo1.Sumw2();
	MHTMETCalo1.Divide(&MHTMETCalo2);
	MHTMETCalo1.SetMarkerStyle(7);
	MHTMETCalo1.GetXaxis()->SetTitle("MHTMETCalo");
	MHTMETCalo1.GetYaxis()->SetTitle("Full/Fast");
	MHTMETCalo1.GetYaxis()->SetRangeUser(0,2);
	MHTMETCalo1.SetLabelSize(0.08, "X");
	MHTMETCalo1.SetLabelSize(0.07, "Y");
	MHTMETCalo1.SetTitleSize(0.09, "X");
	MHTMETCalo1.SetTitleSize(0.09, "Y");
	MHTMETCalo1.SetTitleOffset(0.25, "Y");
	MHTMETCalo1.Draw("p");
	c2->cd();

	if( printFinalPlots ) c2->Print("../results/MHToverMET_log_ratio.pdf");
	c2->Print("../test.pdf");

	// ******************************************************** //

	pad1->cd();
	test_names.push_back("MHToverMET_typeIPFMet_distro_h_;1");

	TH1D MHTMETtypeIPF1;
	MHTMETtypeIPF1.Sumw2();
	MHTMETtypeIPF1 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFull,vHTBins_beforeCuts, test_names.at(14) );
	MHTMETtypeIPF1.SetLineColor(kBlue);
	MHTMETtypeIPF1.Rebin(10);
	MHTMETtypeIPF1.GetXaxis()->SetRangeUser(0,1500);

	TH1D MHTMETtypeIPF2;
	MHTMETtypeIPF2.Sumw2();
	MHTMETtypeIPF2 = *pHists1D.addHistForDiffFoldersAndFiles1D( vInFilesFast,vHTBins_beforeCuts, test_names.at(14) );
	MHTMETtypeIPF2.SetLineColor(kRed);
	MHTMETtypeIPF2.Rebin(10);
	MHTMETtypeIPF2.GetXaxis()->SetRangeUser(0,1500);

	MHTMETtypeIPF1.Scale(fullScaleF);
	MHTMETtypeIPF2.Scale(fastScaleF);

	MHTMETtypeIPF1.DrawCopy("hist");
	MHTMETtypeIPF2.Draw("histSAME");

	c2->cd();
	pad2->cd();

	MHTMETtypeIPF1.SetStats(0);
	MHTMETtypeIPF1.Sumw2();
	MHTMETtypeIPF1.Divide(&MHTMETtypeIPF2);
	MHTMETtypeIPF1.SetMarkerStyle(7);
	MHTMETtypeIPF1.GetXaxis()->SetTitle("MHTMETtypeIPF");
	MHTMETtypeIPF1.GetYaxis()->SetTitle("Full/Fast");
	MHTMETtypeIPF1.GetYaxis()->SetRangeUser(0,2);
	MHTMETtypeIPF1.SetLabelSize(0.08, "X");
	MHTMETtypeIPF1.SetLabelSize(0.07, "Y");
	MHTMETtypeIPF1.SetTitleSize(0.09, "X");
	MHTMETtypeIPF1.SetTitleSize(0.09, "Y");
	MHTMETtypeIPF1.SetTitleOffset(0.25, "Y");
	MHTMETtypeIPF1.Draw("p");
	c2->cd();

	if( printFinalPlots ) c2->Print("../results/MHToverMET_log_ratio.pdf");
	c2->Print("../test.pdf)");


}




















