#include <math.h>
#include <algorithm>

#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/audio/dummy-audio.h"

using std::max;
using std::min;

/* ------------------------------------------------------------
name: "cubic_distortion"
Code generated with Faust 2.0.a51 (http://faust.grame.fr)
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  

#include <math.h>

float faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

class mydsp : public dsp {
	
  private:
	
	int fSamplingFreq;
	int iVec0[2];
	float fRec18[3];
	float fRec17[3];
	float fRec16[3];
	float fRec15[3];
	float fRec14[3];
	float fRec13[3];
	float fRec12[3];
	float fRec11[3];
	float fRec10[3];
	float fRec9[3];
	float fRec8[3];
	float fRec7[3];
	float fRec6[3];
	float fRec5[3];
	float fRec4[3];
	float fRec3[3];
	float fRec2[3];
	float fRec1[3];
	float fRec29[3];
	float fRec28[3];
	float fRec27[3];
	float fRec57[3];
	float fRec56[3];
	float fRec55[3];
	float fRec54[3];
	float fRec53[3];
	float fRec52[3];
	float fRec51[3];
	float fRec50[3];
	float fRec49[3];
	float fRec48[3];
	float fRec47[3];
	float fRec46[3];
	float fRec45[3];
	float fRec44[3];
	float fRec43[3];
	float fRec42[3];
	float fRec41[3];
	float fRec40[3];
	float fRec39[3];
	float fRec38[3];
	float fRec37[3];
	float fRec36[3];
	float fRec35[3];
	float fRec34[3];
	float fRec33[3];
	float fRec32[3];
	float fRec31[3];
	float fRec61[3];
	float fRec60[3];
	float fRec59[3];
	float fRec65[3];
	float fRec64[3];
	float fRec63[3];
	float fRec69[3];
	float fRec68[3];
	float fRec67[3];
	float fRec73[3];
	float fRec72[3];
	float fRec71[3];
	float fRec77[3];
	float fRec76[3];
	float fRec75[3];
	float fRec81[3];
	float fRec80[3];
	float fRec79[3];
	float fRec85[3];
	float fRec84[3];
	float fRec83[3];
	float fRec89[3];
	float fRec88[3];
	float fRec87[3];
	float fRec93[3];
	float fRec92[3];
	float fRec91[3];
	float fRec97[3];
	float fRec96[3];
	float fRec95[3];
	float fRec101[3];
	float fRec100[3];
	float fRec99[3];
	float fRec105[3];
	float fRec104[3];
	float fRec103[3];
	float fRec20[2];
	float fRec23[2];
	float fRec21[2];
	float fRec22[2];
	float fRec24[2];
	float fRec25[2];
	float fVec1[2];
	float fRec19[2];
	float fRec0[2];
	float fRec26[2];
	float fRec30[2];
	float fRec58[2];
	float fRec62[2];
	float fRec66[2];
	float fRec70[2];
	float fRec74[2];
	float fRec78[2];
	float fRec82[2];
	float fRec86[2];
	float fRec90[2];
	float fRec94[2];
	float fRec98[2];
	float fRec102[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fConst15;
	float fConst16;
	float fConst17;
	float fConst18;
	float fConst19;
	float fConst20;
	float fConst21;
	float fConst22;
	float fConst23;
	float fConst24;
	float fConst25;
	float fConst26;
	float fConst27;
	float fConst28;
	float fConst29;
	float fConst30;
	float fConst31;
	float fConst32;
	float fConst33;
	float fConst34;
	float fConst35;
	float fConst36;
	float fConst37;
	float fConst38;
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fConst44;
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fConst51;
	float fConst52;
	float fConst53;
	float fConst54;
	float fConst55;
	float fConst56;
	float fConst57;
	float fConst58;
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
	float fConst67;
	float fConst68;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHslider2;
	float fConst69;
	FAUSTFLOAT fHslider3;
	float fConst70;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fHslider5;
	FAUSTFLOAT fHslider6;
	float fConst71;
	float fConst72;
	float fConst73;
	float fConst74;
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fConst79;
	float fConst80;
	float fConst81;
	float fConst82;
	float fConst83;
	float fConst84;
	float fConst85;
	float fConst86;
	float fConst87;
	float fConst88;
	float fConst89;
	float fConst90;
	float fConst91;
	float fConst92;
	float fConst93;
	float fConst94;
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	float fConst99;
	float fConst100;
	float fConst101;
	float fConst102;
	float fConst103;
	float fConst104;
	float fConst105;
	float fConst106;
	float fConst107;
	float fConst108;
	float fConst109;
	float fConst110;
	float fConst111;
	float fConst112;
	float fConst113;
	float fConst114;
	float fConst115;
	float fConst116;
	float fConst117;
	float fConst118;
	float fConst119;
	float fConst120;
	float fConst121;
	float fConst122;
	float fConst123;
	float fConst124;
	float fConst125;
	FAUSTFLOAT fVbargraph0;
	float fConst126;
	float fConst127;
	float fConst128;
	float fConst129;
	float fConst130;
	float fConst131;
	float fConst132;
	float fConst133;
	float fConst134;
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fConst139;
	float fConst140;
	float fConst141;
	float fConst142;
	float fConst143;
	FAUSTFLOAT fVbargraph1;
	float fConst144;
	float fConst145;
	float fConst146;
	float fConst147;
	float fConst148;
	float fConst149;
	float fConst150;
	float fConst151;
	float fConst152;
	float fConst153;
	float fConst154;
	float fConst155;
	float fConst156;
	float fConst157;
	float fConst158;
	float fConst159;
	float fConst160;
	float fConst161;
	float fConst162;
	float fConst163;
	float fConst164;
	float fConst165;
	float fConst166;
	float fConst167;
	float fConst168;
	float fConst169;
	float fConst170;
	float fConst171;
	float fConst172;
	float fConst173;
	float fConst174;
	float fConst175;
	float fConst176;
	float fConst177;
	float fConst178;
	float fConst179;
	float fConst180;
	float fConst181;
	float fConst182;
	float fConst183;
	float fConst184;
	float fConst185;
	float fConst186;
	float fConst187;
	float fConst188;
	float fConst189;
	float fConst190;
	float fConst191;
	float fConst192;
	float fConst193;
	float fConst194;
	float fConst195;
	float fConst196;
	float fConst197;
	float fConst198;
	float fConst199;
	float fConst200;
	float fConst201;
	float fConst202;
	float fConst203;
	float fConst204;
	float fConst205;
	float fConst206;
	float fConst207;
	float fConst208;
	float fConst209;
	float fConst210;
	float fConst211;
	float fConst212;
	float fConst213;
	float fConst214;
	float fConst215;
	float fConst216;
	float fConst217;
	float fConst218;
	float fConst219;
	float fConst220;
	float fConst221;
	float fConst222;
	float fConst223;
	float fConst224;
	float fConst225;
	float fConst226;
	float fConst227;
	float fConst228;
	float fConst229;
	float fConst230;
	float fConst231;
	float fConst232;
	float fConst233;
	float fConst234;
	float fConst235;
	float fConst236;
	float fConst237;
	float fConst238;
	float fConst239;
	float fConst240;
	float fConst241;
	float fConst242;
	float fConst243;
	float fConst244;
	float fConst245;
	float fConst246;
	float fConst247;
	float fConst248;
	float fConst249;
	float fConst250;
	float fConst251;
	float fConst252;
	float fConst253;
	float fConst254;
	float fConst255;
	float fConst256;
	float fConst257;
	float fConst258;
	float fConst259;
	float fConst260;
	float fConst261;
	float fConst262;
	float fConst263;
	float fConst264;
	float fConst265;
	float fConst266;
	float fConst267;
	float fConst268;
	float fConst269;
	float fConst270;
	float fConst271;
	float fConst272;
	float fConst273;
	float fConst274;
	float fConst275;
	float fConst276;
	float fConst277;
	float fConst278;
	float fConst279;
	float fConst280;
	float fConst281;
	float fConst282;
	float fConst283;
	float fConst284;
	float fConst285;
	float fConst286;
	float fConst287;
	float fConst288;
	float fConst289;
	float fConst290;
	float fConst291;
	float fConst292;
	float fConst293;
	float fConst294;
	float fConst295;
	float fConst296;
	float fConst297;
	float fConst298;
	float fConst299;
	float fConst300;
	float fConst301;
	float fConst302;
	float fConst303;
	float fConst304;
	float fConst305;
	float fConst306;
	float fConst307;
	float fConst308;
	float fConst309;
	float fConst310;
	float fConst311;
	float fConst312;
	float fConst313;
	float fConst314;
	float fConst315;
	float fConst316;
	float fConst317;
	float fConst318;
	float fConst319;
	FAUSTFLOAT fVbargraph2;
	float fConst320;
	float fConst321;
	float fConst322;
	float fConst323;
	float fConst324;
	float fConst325;
	float fConst326;
	float fConst327;
	float fConst328;
	float fConst329;
	float fConst330;
	float fConst331;
	float fConst332;
	float fConst333;
	float fConst334;
	float fConst335;
	float fConst336;
	float fConst337;
	FAUSTFLOAT fVbargraph3;
	float fConst338;
	float fConst339;
	float fConst340;
	float fConst341;
	float fConst342;
	float fConst343;
	float fConst344;
	float fConst345;
	float fConst346;
	float fConst347;
	float fConst348;
	float fConst349;
	float fConst350;
	float fConst351;
	float fConst352;
	float fConst353;
	float fConst354;
	float fConst355;
	FAUSTFLOAT fVbargraph4;
	float fConst356;
	float fConst357;
	float fConst358;
	float fConst359;
	float fConst360;
	float fConst361;
	float fConst362;
	float fConst363;
	float fConst364;
	float fConst365;
	float fConst366;
	float fConst367;
	float fConst368;
	float fConst369;
	float fConst370;
	float fConst371;
	float fConst372;
	float fConst373;
	FAUSTFLOAT fVbargraph5;
	float fConst374;
	float fConst375;
	float fConst376;
	float fConst377;
	float fConst378;
	float fConst379;
	float fConst380;
	float fConst381;
	float fConst382;
	float fConst383;
	float fConst384;
	float fConst385;
	float fConst386;
	float fConst387;
	float fConst388;
	float fConst389;
	float fConst390;
	float fConst391;
	FAUSTFLOAT fVbargraph6;
	float fConst392;
	float fConst393;
	float fConst394;
	float fConst395;
	float fConst396;
	float fConst397;
	float fConst398;
	float fConst399;
	float fConst400;
	float fConst401;
	float fConst402;
	float fConst403;
	float fConst404;
	float fConst405;
	float fConst406;
	float fConst407;
	float fConst408;
	float fConst409;
	FAUSTFLOAT fVbargraph7;
	float fConst410;
	float fConst411;
	float fConst412;
	float fConst413;
	float fConst414;
	float fConst415;
	float fConst416;
	float fConst417;
	float fConst418;
	float fConst419;
	float fConst420;
	float fConst421;
	float fConst422;
	float fConst423;
	float fConst424;
	float fConst425;
	float fConst426;
	float fConst427;
	FAUSTFLOAT fVbargraph8;
	float fConst428;
	float fConst429;
	float fConst430;
	float fConst431;
	float fConst432;
	float fConst433;
	float fConst434;
	float fConst435;
	float fConst436;
	float fConst437;
	float fConst438;
	float fConst439;
	float fConst440;
	float fConst441;
	float fConst442;
	float fConst443;
	float fConst444;
	float fConst445;
	FAUSTFLOAT fVbargraph9;
	float fConst446;
	float fConst447;
	float fConst448;
	float fConst449;
	float fConst450;
	float fConst451;
	float fConst452;
	float fConst453;
	float fConst454;
	float fConst455;
	float fConst456;
	float fConst457;
	float fConst458;
	float fConst459;
	float fConst460;
	float fConst461;
	float fConst462;
	float fConst463;
	FAUSTFLOAT fVbargraph10;
	float fConst464;
	float fConst465;
	float fConst466;
	float fConst467;
	float fConst468;
	float fConst469;
	float fConst470;
	float fConst471;
	float fConst472;
	float fConst473;
	float fConst474;
	float fConst475;
	float fConst476;
	float fConst477;
	float fConst478;
	float fConst479;
	float fConst480;
	float fConst481;
	FAUSTFLOAT fVbargraph11;
	float fConst482;
	float fConst483;
	float fConst484;
	float fConst485;
	float fConst486;
	float fConst487;
	float fConst488;
	float fConst489;
	float fConst490;
	float fConst491;
	float fConst492;
	float fConst493;
	float fConst494;
	float fConst495;
	float fConst496;
	float fConst497;
	float fConst498;
	float fConst499;
	FAUSTFLOAT fVbargraph12;
	float fConst500;
	float fConst501;
	float fConst502;
	float fConst503;
	float fConst504;
	float fConst505;
	float fConst506;
	float fConst507;
	float fConst508;
	float fConst509;
	float fConst510;
	float fConst511;
	float fConst512;
	float fConst513;
	float fConst514;
	float fConst515;
	float fConst516;
	float fConst517;
	FAUSTFLOAT fVbargraph13;
	float fConst518;
	float fConst519;
	float fConst520;
	float fConst521;
	float fConst522;
	float fConst523;
	float fConst524;
	float fConst525;
	float fConst526;
	float fConst527;
	float fConst528;
	float fConst529;
	float fConst530;
	float fConst531;
	float fConst532;
	float fConst533;
	float fConst534;
	float fConst535;
	FAUSTFLOAT fVbargraph14;
	
  public:
	
	void metadata(Meta* m) { 
		m->declare("effect.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("effect.lib/copyright", "Julius O. Smith III");
		m->declare("effect.lib/exciter_author", "Priyanka Shekar (pshekar@ccrma.stanford.edu)");
		m->declare("effect.lib/exciter_copyright", "Copyright (c) 2013 Priyanka Shekar");
		m->declare("effect.lib/exciter_license", "MIT License (MIT)");
		m->declare("effect.lib/exciter_name", "Harmonic Exciter");
		m->declare("effect.lib/exciter_version", "1.0");
		m->declare("effect.lib/license", "STK-4.3");
		m->declare("effect.lib/name", "Faust Audio Effect Library");
		m->declare("effect.lib/version", "1.33");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "cubic_distortion");
		m->declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("oscillator.lib/copyright", "Julius O. Smith III");
		m->declare("oscillator.lib/license", "STK-4.3");
		m->declare("oscillator.lib/name", "Faust Oscillator Library");
		m->declare("oscillator.lib/version", "1.11");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	static void classInit(int samplingFreq) {
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (1000.0f / fConst0);
		fConst2 = tanf((4986.96729f / fConst0));
		fConst3 = (1.0f / fConst2);
		fConst4 = (1.0f / (((fConst3 + 0.157482162f) / fConst2) + 0.935140193f));
		fConst5 = faustpower2_f(fConst2);
		fConst6 = (50.0638084f / fConst5);
		fConst7 = (fConst6 + 0.935140193f);
		fConst8 = (1.0f / (((fConst3 + 0.743130445f) / fConst2) + 1.4500711f));
		fConst9 = (11.0520525f / fConst5);
		fConst10 = (fConst9 + 1.4500711f);
		fConst11 = (1.0f / (((fConst3 + 3.18972731f) / fConst2) + 4.07678175f));
		fConst12 = (0.00176617282f / fConst5);
		fConst13 = (fConst12 + 0.000407678192f);
		fConst14 = tanf((7916.31738f / fConst0));
		fConst15 = (1.0f / fConst14);
		fConst16 = (1.0f / (((fConst15 + 0.168404877f) / fConst14) + 1.06935835f));
		fConst17 = faustpower2_f(fConst14);
		fConst18 = (1.0f / fConst17);
		fConst19 = (fConst18 + 53.5361519f);
		fConst20 = (1.0f / (((fConst15 + 0.51247865f) / fConst14) + 0.689621389f));
		fConst21 = (fConst18 + 7.62173128f);
		fConst22 = (1.0f / (((fConst15 + 0.782413065f) / fConst14) + 0.245291501f));
		fConst23 = (9.99999975e-05f / fConst17);
		fConst24 = (fConst23 + 0.000433227193f);
		fConst25 = tanf((12566.3711f / fConst0));
		fConst26 = (1.0f / fConst25);
		fConst27 = (1.0f / (((fConst26 + 0.168404877f) / fConst25) + 1.06935835f));
		fConst28 = faustpower2_f(fConst25);
		fConst29 = (1.0f / fConst28);
		fConst30 = (fConst29 + 53.5361519f);
		fConst31 = (1.0f / (((fConst26 + 0.51247865f) / fConst25) + 0.689621389f));
		fConst32 = (fConst29 + 7.62173128f);
		fConst33 = (1.0f / (((fConst26 + 0.782413065f) / fConst25) + 0.245291501f));
		fConst34 = (9.99999975e-05f / fConst28);
		fConst35 = (fConst34 + 0.000433227193f);
		fConst36 = tanf((19947.8691f / fConst0));
		fConst37 = (1.0f / fConst36);
		fConst38 = (1.0f / (((fConst37 + 0.168404877f) / fConst36) + 1.06935835f));
		fConst39 = faustpower2_f(fConst36);
		fConst40 = (1.0f / fConst39);
		fConst41 = (fConst40 + 53.5361519f);
		fConst42 = (1.0f / (((fConst37 + 0.51247865f) / fConst36) + 0.689621389f));
		fConst43 = (fConst40 + 7.62173128f);
		fConst44 = (1.0f / (((fConst37 + 0.782413065f) / fConst36) + 0.245291501f));
		fConst45 = (9.99999975e-05f / fConst39);
		fConst46 = (fConst45 + 0.000433227193f);
		fConst47 = tanf((31665.2695f / fConst0));
		fConst48 = (1.0f / fConst47);
		fConst49 = (1.0f / (((fConst48 + 0.168404877f) / fConst47) + 1.06935835f));
		fConst50 = faustpower2_f(fConst47);
		fConst51 = (1.0f / fConst50);
		fConst52 = (fConst51 + 53.5361519f);
		fConst53 = (1.0f / (((fConst48 + 0.51247865f) / fConst47) + 0.689621389f));
		fConst54 = (fConst51 + 7.62173128f);
		fConst55 = (1.0f / (((fConst48 + 0.782413065f) / fConst47) + 0.245291501f));
		fConst56 = (9.99999975e-05f / fConst50);
		fConst57 = (fConst56 + 0.000433227193f);
		fConst58 = tanf((50265.4844f / fConst0));
		fConst59 = (1.0f / fConst58);
		fConst60 = (1.0f / (((fConst59 + 0.168404877f) / fConst58) + 1.06935835f));
		fConst61 = faustpower2_f(fConst58);
		fConst62 = (1.0f / fConst61);
		fConst63 = (fConst62 + 53.5361519f);
		fConst64 = (1.0f / (((fConst59 + 0.51247865f) / fConst58) + 0.689621389f));
		fConst65 = (fConst62 + 7.62173128f);
		fConst66 = (1.0f / (((fConst59 + 0.782413065f) / fConst58) + 0.245291501f));
		fConst67 = (9.99999975e-05f / fConst61);
		fConst68 = (fConst67 + 0.000433227193f);
		fConst69 = (6.28318548f / fConst0);
		fConst70 = (1.0f / fConst0);
		fConst71 = (((fConst59 + -0.782413065f) / fConst58) + 0.245291501f);
		fConst72 = (2.0f * (0.245291501f - fConst62));
		fConst73 = (2.0f * (0.000433227193f - fConst67));
		fConst74 = (((fConst59 + -0.51247865f) / fConst58) + 0.689621389f);
		fConst75 = (2.0f * (0.689621389f - fConst62));
		fConst76 = (2.0f * (7.62173128f - fConst62));
		fConst77 = (((fConst59 + -0.168404877f) / fConst58) + 1.06935835f);
		fConst78 = (2.0f * (1.06935835f - fConst62));
		fConst79 = (2.0f * (53.5361519f - fConst62));
		fConst80 = (((fConst48 + -0.782413065f) / fConst47) + 0.245291501f);
		fConst81 = (2.0f * (0.245291501f - fConst51));
		fConst82 = (2.0f * (0.000433227193f - fConst56));
		fConst83 = (((fConst48 + -0.51247865f) / fConst47) + 0.689621389f);
		fConst84 = (2.0f * (0.689621389f - fConst51));
		fConst85 = (2.0f * (7.62173128f - fConst51));
		fConst86 = (((fConst48 + -0.168404877f) / fConst47) + 1.06935835f);
		fConst87 = (2.0f * (1.06935835f - fConst51));
		fConst88 = (2.0f * (53.5361519f - fConst51));
		fConst89 = (((fConst37 + -0.782413065f) / fConst36) + 0.245291501f);
		fConst90 = (2.0f * (0.245291501f - fConst40));
		fConst91 = (2.0f * (0.000433227193f - fConst45));
		fConst92 = (((fConst37 + -0.51247865f) / fConst36) + 0.689621389f);
		fConst93 = (2.0f * (0.689621389f - fConst40));
		fConst94 = (2.0f * (7.62173128f - fConst40));
		fConst95 = (((fConst37 + -0.168404877f) / fConst36) + 1.06935835f);
		fConst96 = (2.0f * (1.06935835f - fConst40));
		fConst97 = (2.0f * (53.5361519f - fConst40));
		fConst98 = (((fConst26 + -0.782413065f) / fConst25) + 0.245291501f);
		fConst99 = (2.0f * (0.245291501f - fConst29));
		fConst100 = (2.0f * (0.000433227193f - fConst34));
		fConst101 = (((fConst26 + -0.51247865f) / fConst25) + 0.689621389f);
		fConst102 = (2.0f * (0.689621389f - fConst29));
		fConst103 = (2.0f * (7.62173128f - fConst29));
		fConst104 = (((fConst26 + -0.168404877f) / fConst25) + 1.06935835f);
		fConst105 = (2.0f * (1.06935835f - fConst29));
		fConst106 = (2.0f * (53.5361519f - fConst29));
		fConst107 = (((fConst15 + -0.782413065f) / fConst14) + 0.245291501f);
		fConst108 = (2.0f * (0.245291501f - fConst18));
		fConst109 = (2.0f * (0.000433227193f - fConst23));
		fConst110 = (((fConst15 + -0.51247865f) / fConst14) + 0.689621389f);
		fConst111 = (2.0f * (0.689621389f - fConst18));
		fConst112 = (2.0f * (7.62173128f - fConst18));
		fConst113 = (((fConst15 + -0.168404877f) / fConst14) + 1.06935835f);
		fConst114 = (2.0f * (1.06935835f - fConst18));
		fConst115 = (2.0f * (53.5361519f - fConst18));
		fConst116 = (((fConst3 + -3.18972731f) / fConst2) + 4.07678175f);
		fConst117 = (1.0f / fConst5);
		fConst118 = (2.0f * (4.07678175f - fConst117));
		fConst119 = (2.0f * (0.000407678192f - fConst12));
		fConst120 = (((fConst3 + -0.743130445f) / fConst2) + 1.4500711f);
		fConst121 = (2.0f * (1.4500711f - fConst117));
		fConst122 = (2.0f * (1.4500711f - fConst9));
		fConst123 = (((fConst3 + -0.157482162f) / fConst2) + 0.935140193f);
		fConst124 = (2.0f * (0.935140193f - fConst117));
		fConst125 = (2.0f * (0.935140193f - fConst6));
		fConst126 = (1.0f / (((fConst15 + 0.157482162f) / fConst14) + 0.935140193f));
		fConst127 = (50.0638084f / fConst17);
		fConst128 = (fConst127 + 0.935140193f);
		fConst129 = (1.0f / (((fConst15 + 0.743130445f) / fConst14) + 1.4500711f));
		fConst130 = (11.0520525f / fConst17);
		fConst131 = (fConst130 + 1.4500711f);
		fConst132 = (1.0f / (((fConst15 + 3.18972731f) / fConst14) + 4.07678175f));
		fConst133 = (0.00176617282f / fConst17);
		fConst134 = (fConst133 + 0.000407678192f);
		fConst135 = (((fConst15 + -3.18972731f) / fConst14) + 4.07678175f);
		fConst136 = (2.0f * (4.07678175f - fConst18));
		fConst137 = (2.0f * (0.000407678192f - fConst133));
		fConst138 = (((fConst15 + -0.743130445f) / fConst14) + 1.4500711f);
		fConst139 = (2.0f * (1.4500711f - fConst18));
		fConst140 = (2.0f * (1.4500711f - fConst130));
		fConst141 = (((fConst15 + -0.157482162f) / fConst14) + 0.935140193f);
		fConst142 = (2.0f * (0.935140193f - fConst18));
		fConst143 = (2.0f * (0.935140193f - fConst127));
		fConst144 = tanf((123.692459f / fConst0));
		fConst145 = (1.0f / fConst144);
		fConst146 = (1.0f / (((fConst145 + 0.168404877f) / fConst144) + 1.06935835f));
		fConst147 = faustpower2_f(fConst144);
		fConst148 = (1.0f / fConst147);
		fConst149 = (fConst148 + 53.5361519f);
		fConst150 = (1.0f / (((fConst145 + 0.51247865f) / fConst144) + 0.689621389f));
		fConst151 = (fConst148 + 7.62173128f);
		fConst152 = (1.0f / (((fConst145 + 0.782413065f) / fConst144) + 0.245291501f));
		fConst153 = (9.99999975e-05f / fConst147);
		fConst154 = (fConst153 + 0.000433227193f);
		fConst155 = tanf((196.349548f / fConst0));
		fConst156 = (1.0f / fConst155);
		fConst157 = (1.0f / (((fConst156 + 0.168404877f) / fConst155) + 1.06935835f));
		fConst158 = faustpower2_f(fConst155);
		fConst159 = (1.0f / fConst158);
		fConst160 = (fConst159 + 53.5361519f);
		fConst161 = (1.0f / (((fConst156 + 0.51247865f) / fConst155) + 0.689621389f));
		fConst162 = (fConst159 + 7.62173128f);
		fConst163 = (1.0f / (((fConst156 + 0.782413065f) / fConst155) + 0.245291501f));
		fConst164 = (9.99999975e-05f / fConst158);
		fConst165 = (fConst164 + 0.000433227193f);
		fConst166 = tanf((311.685455f / fConst0));
		fConst167 = (1.0f / fConst166);
		fConst168 = (1.0f / (((fConst167 + 0.168404877f) / fConst166) + 1.06935835f));
		fConst169 = faustpower2_f(fConst166);
		fConst170 = (1.0f / fConst169);
		fConst171 = (fConst170 + 53.5361519f);
		fConst172 = (1.0f / (((fConst167 + 0.51247865f) / fConst166) + 0.689621389f));
		fConst173 = (fConst170 + 7.62173128f);
		fConst174 = (1.0f / (((fConst167 + 0.782413065f) / fConst166) + 0.245291501f));
		fConst175 = (9.99999975e-05f / fConst169);
		fConst176 = (fConst175 + 0.000433227193f);
		fConst177 = tanf((494.769836f / fConst0));
		fConst178 = (1.0f / fConst177);
		fConst179 = (1.0f / (((fConst178 + 0.168404877f) / fConst177) + 1.06935835f));
		fConst180 = faustpower2_f(fConst177);
		fConst181 = (1.0f / fConst180);
		fConst182 = (fConst181 + 53.5361519f);
		fConst183 = (1.0f / (((fConst178 + 0.51247865f) / fConst177) + 0.689621389f));
		fConst184 = (fConst181 + 7.62173128f);
		fConst185 = (1.0f / (((fConst178 + 0.782413065f) / fConst177) + 0.245291501f));
		fConst186 = (9.99999975e-05f / fConst180);
		fConst187 = (fConst186 + 0.000433227193f);
		fConst188 = tanf((785.398193f / fConst0));
		fConst189 = (1.0f / fConst188);
		fConst190 = (1.0f / (((fConst189 + 0.168404877f) / fConst188) + 1.06935835f));
		fConst191 = faustpower2_f(fConst188);
		fConst192 = (1.0f / fConst191);
		fConst193 = (fConst192 + 53.5361519f);
		fConst194 = (1.0f / (((fConst189 + 0.51247865f) / fConst188) + 0.689621389f));
		fConst195 = (fConst192 + 7.62173128f);
		fConst196 = (1.0f / (((fConst189 + 0.782413065f) / fConst188) + 0.245291501f));
		fConst197 = (9.99999975e-05f / fConst191);
		fConst198 = (fConst197 + 0.000433227193f);
		fConst199 = tanf((1246.74182f / fConst0));
		fConst200 = (1.0f / fConst199);
		fConst201 = (1.0f / (((fConst200 + 0.168404877f) / fConst199) + 1.06935835f));
		fConst202 = faustpower2_f(fConst199);
		fConst203 = (1.0f / fConst202);
		fConst204 = (fConst203 + 53.5361519f);
		fConst205 = (1.0f / (((fConst200 + 0.51247865f) / fConst199) + 0.689621389f));
		fConst206 = (fConst203 + 7.62173128f);
		fConst207 = (1.0f / (((fConst200 + 0.782413065f) / fConst199) + 0.245291501f));
		fConst208 = (9.99999975e-05f / fConst202);
		fConst209 = (fConst208 + 0.000433227193f);
		fConst210 = tanf((1979.07935f / fConst0));
		fConst211 = (1.0f / fConst210);
		fConst212 = (1.0f / (((fConst211 + 0.168404877f) / fConst210) + 1.06935835f));
		fConst213 = faustpower2_f(fConst210);
		fConst214 = (1.0f / fConst213);
		fConst215 = (fConst214 + 53.5361519f);
		fConst216 = (1.0f / (((fConst211 + 0.51247865f) / fConst210) + 0.689621389f));
		fConst217 = (fConst214 + 7.62173128f);
		fConst218 = (1.0f / (((fConst211 + 0.782413065f) / fConst210) + 0.245291501f));
		fConst219 = (9.99999975e-05f / fConst213);
		fConst220 = (fConst219 + 0.000433227193f);
		fConst221 = tanf((3141.59277f / fConst0));
		fConst222 = (1.0f / fConst221);
		fConst223 = (1.0f / (((fConst222 + 0.168404877f) / fConst221) + 1.06935835f));
		fConst224 = faustpower2_f(fConst221);
		fConst225 = (1.0f / fConst224);
		fConst226 = (fConst225 + 53.5361519f);
		fConst227 = (1.0f / (((fConst222 + 0.51247865f) / fConst221) + 0.689621389f));
		fConst228 = (fConst225 + 7.62173128f);
		fConst229 = (1.0f / (((fConst222 + 0.782413065f) / fConst221) + 0.245291501f));
		fConst230 = (9.99999975e-05f / fConst224);
		fConst231 = (fConst230 + 0.000433227193f);
		fConst232 = (1.0f / (((fConst3 + 0.168404877f) / fConst2) + 1.06935835f));
		fConst233 = (fConst117 + 53.5361519f);
		fConst234 = (1.0f / (((fConst3 + 0.51247865f) / fConst2) + 0.689621389f));
		fConst235 = (fConst117 + 7.62173128f);
		fConst236 = (1.0f / (((fConst3 + 0.782413065f) / fConst2) + 0.245291501f));
		fConst237 = (9.99999975e-05f / fConst5);
		fConst238 = (fConst237 + 0.000433227193f);
		fConst239 = (((fConst3 + -0.782413065f) / fConst2) + 0.245291501f);
		fConst240 = (2.0f * (0.245291501f - fConst117));
		fConst241 = (2.0f * (0.000433227193f - fConst237));
		fConst242 = (((fConst3 + -0.51247865f) / fConst2) + 0.689621389f);
		fConst243 = (2.0f * (0.689621389f - fConst117));
		fConst244 = (2.0f * (7.62173128f - fConst117));
		fConst245 = (((fConst3 + -0.168404877f) / fConst2) + 1.06935835f);
		fConst246 = (2.0f * (1.06935835f - fConst117));
		fConst247 = (2.0f * (53.5361519f - fConst117));
		fConst248 = (((fConst222 + -0.782413065f) / fConst221) + 0.245291501f);
		fConst249 = (2.0f * (0.245291501f - fConst225));
		fConst250 = (2.0f * (0.000433227193f - fConst230));
		fConst251 = (((fConst222 + -0.51247865f) / fConst221) + 0.689621389f);
		fConst252 = (2.0f * (0.689621389f - fConst225));
		fConst253 = (2.0f * (7.62173128f - fConst225));
		fConst254 = (((fConst222 + -0.168404877f) / fConst221) + 1.06935835f);
		fConst255 = (2.0f * (1.06935835f - fConst225));
		fConst256 = (2.0f * (53.5361519f - fConst225));
		fConst257 = (((fConst211 + -0.782413065f) / fConst210) + 0.245291501f);
		fConst258 = (2.0f * (0.245291501f - fConst214));
		fConst259 = (2.0f * (0.000433227193f - fConst219));
		fConst260 = (((fConst211 + -0.51247865f) / fConst210) + 0.689621389f);
		fConst261 = (2.0f * (0.689621389f - fConst214));
		fConst262 = (2.0f * (7.62173128f - fConst214));
		fConst263 = (((fConst211 + -0.168404877f) / fConst210) + 1.06935835f);
		fConst264 = (2.0f * (1.06935835f - fConst214));
		fConst265 = (2.0f * (53.5361519f - fConst214));
		fConst266 = (((fConst200 + -0.782413065f) / fConst199) + 0.245291501f);
		fConst267 = (2.0f * (0.245291501f - fConst203));
		fConst268 = (2.0f * (0.000433227193f - fConst208));
		fConst269 = (((fConst200 + -0.51247865f) / fConst199) + 0.689621389f);
		fConst270 = (2.0f * (0.689621389f - fConst203));
		fConst271 = (2.0f * (7.62173128f - fConst203));
		fConst272 = (((fConst200 + -0.168404877f) / fConst199) + 1.06935835f);
		fConst273 = (2.0f * (1.06935835f - fConst203));
		fConst274 = (2.0f * (53.5361519f - fConst203));
		fConst275 = (((fConst189 + -0.782413065f) / fConst188) + 0.245291501f);
		fConst276 = (2.0f * (0.245291501f - fConst192));
		fConst277 = (2.0f * (0.000433227193f - fConst197));
		fConst278 = (((fConst189 + -0.51247865f) / fConst188) + 0.689621389f);
		fConst279 = (2.0f * (0.689621389f - fConst192));
		fConst280 = (2.0f * (7.62173128f - fConst192));
		fConst281 = (((fConst189 + -0.168404877f) / fConst188) + 1.06935835f);
		fConst282 = (2.0f * (1.06935835f - fConst192));
		fConst283 = (2.0f * (53.5361519f - fConst192));
		fConst284 = (((fConst178 + -0.782413065f) / fConst177) + 0.245291501f);
		fConst285 = (2.0f * (0.245291501f - fConst181));
		fConst286 = (2.0f * (0.000433227193f - fConst186));
		fConst287 = (((fConst178 + -0.51247865f) / fConst177) + 0.689621389f);
		fConst288 = (2.0f * (0.689621389f - fConst181));
		fConst289 = (2.0f * (7.62173128f - fConst181));
		fConst290 = (((fConst178 + -0.168404877f) / fConst177) + 1.06935835f);
		fConst291 = (2.0f * (1.06935835f - fConst181));
		fConst292 = (2.0f * (53.5361519f - fConst181));
		fConst293 = (((fConst167 + -0.782413065f) / fConst166) + 0.245291501f);
		fConst294 = (2.0f * (0.245291501f - fConst170));
		fConst295 = (2.0f * (0.000433227193f - fConst175));
		fConst296 = (((fConst167 + -0.51247865f) / fConst166) + 0.689621389f);
		fConst297 = (2.0f * (0.689621389f - fConst170));
		fConst298 = (2.0f * (7.62173128f - fConst170));
		fConst299 = (((fConst167 + -0.168404877f) / fConst166) + 1.06935835f);
		fConst300 = (2.0f * (1.06935835f - fConst170));
		fConst301 = (2.0f * (53.5361519f - fConst170));
		fConst302 = (((fConst156 + -0.782413065f) / fConst155) + 0.245291501f);
		fConst303 = (2.0f * (0.245291501f - fConst159));
		fConst304 = (2.0f * (0.000433227193f - fConst164));
		fConst305 = (((fConst156 + -0.51247865f) / fConst155) + 0.689621389f);
		fConst306 = (2.0f * (0.689621389f - fConst159));
		fConst307 = (2.0f * (7.62173128f - fConst159));
		fConst308 = (((fConst156 + -0.168404877f) / fConst155) + 1.06935835f);
		fConst309 = (2.0f * (1.06935835f - fConst159));
		fConst310 = (2.0f * (53.5361519f - fConst159));
		fConst311 = (((fConst145 + -0.782413065f) / fConst144) + 0.245291501f);
		fConst312 = (2.0f * (0.245291501f - fConst148));
		fConst313 = (2.0f * (0.000433227193f - fConst153));
		fConst314 = (((fConst145 + -0.51247865f) / fConst144) + 0.689621389f);
		fConst315 = (2.0f * (0.689621389f - fConst148));
		fConst316 = (2.0f * (7.62173128f - fConst148));
		fConst317 = (((fConst145 + -0.168404877f) / fConst144) + 1.06935835f);
		fConst318 = (2.0f * (1.06935835f - fConst148));
		fConst319 = (2.0f * (53.5361519f - fConst148));
		fConst320 = (1.0f / (((fConst145 + 0.157482162f) / fConst144) + 0.935140193f));
		fConst321 = (50.0638084f / fConst147);
		fConst322 = (fConst321 + 0.935140193f);
		fConst323 = (1.0f / (((fConst145 + 0.743130445f) / fConst144) + 1.4500711f));
		fConst324 = (11.0520525f / fConst147);
		fConst325 = (fConst324 + 1.4500711f);
		fConst326 = (1.0f / (((fConst145 + 3.18972731f) / fConst144) + 4.07678175f));
		fConst327 = (0.00176617282f / fConst147);
		fConst328 = (fConst327 + 0.000407678192f);
		fConst329 = (((fConst145 + -3.18972731f) / fConst144) + 4.07678175f);
		fConst330 = (2.0f * (4.07678175f - fConst148));
		fConst331 = (2.0f * (0.000407678192f - fConst327));
		fConst332 = (((fConst145 + -0.743130445f) / fConst144) + 1.4500711f);
		fConst333 = (2.0f * (1.4500711f - fConst148));
		fConst334 = (2.0f * (1.4500711f - fConst324));
		fConst335 = (((fConst145 + -0.157482162f) / fConst144) + 0.935140193f);
		fConst336 = (2.0f * (0.935140193f - fConst148));
		fConst337 = (2.0f * (0.935140193f - fConst321));
		fConst338 = (1.0f / (((fConst156 + 0.157482162f) / fConst155) + 0.935140193f));
		fConst339 = (50.0638084f / fConst158);
		fConst340 = (fConst339 + 0.935140193f);
		fConst341 = (1.0f / (((fConst156 + 0.743130445f) / fConst155) + 1.4500711f));
		fConst342 = (11.0520525f / fConst158);
		fConst343 = (fConst342 + 1.4500711f);
		fConst344 = (1.0f / (((fConst156 + 3.18972731f) / fConst155) + 4.07678175f));
		fConst345 = (0.00176617282f / fConst158);
		fConst346 = (fConst345 + 0.000407678192f);
		fConst347 = (((fConst156 + -3.18972731f) / fConst155) + 4.07678175f);
		fConst348 = (2.0f * (4.07678175f - fConst159));
		fConst349 = (2.0f * (0.000407678192f - fConst345));
		fConst350 = (((fConst156 + -0.743130445f) / fConst155) + 1.4500711f);
		fConst351 = (2.0f * (1.4500711f - fConst159));
		fConst352 = (2.0f * (1.4500711f - fConst342));
		fConst353 = (((fConst156 + -0.157482162f) / fConst155) + 0.935140193f);
		fConst354 = (2.0f * (0.935140193f - fConst159));
		fConst355 = (2.0f * (0.935140193f - fConst339));
		fConst356 = (1.0f / (((fConst167 + 0.157482162f) / fConst166) + 0.935140193f));
		fConst357 = (50.0638084f / fConst169);
		fConst358 = (fConst357 + 0.935140193f);
		fConst359 = (1.0f / (((fConst167 + 0.743130445f) / fConst166) + 1.4500711f));
		fConst360 = (11.0520525f / fConst169);
		fConst361 = (fConst360 + 1.4500711f);
		fConst362 = (1.0f / (((fConst167 + 3.18972731f) / fConst166) + 4.07678175f));
		fConst363 = (0.00176617282f / fConst169);
		fConst364 = (fConst363 + 0.000407678192f);
		fConst365 = (((fConst167 + -3.18972731f) / fConst166) + 4.07678175f);
		fConst366 = (2.0f * (4.07678175f - fConst170));
		fConst367 = (2.0f * (0.000407678192f - fConst363));
		fConst368 = (((fConst167 + -0.743130445f) / fConst166) + 1.4500711f);
		fConst369 = (2.0f * (1.4500711f - fConst170));
		fConst370 = (2.0f * (1.4500711f - fConst360));
		fConst371 = (((fConst167 + -0.157482162f) / fConst166) + 0.935140193f);
		fConst372 = (2.0f * (0.935140193f - fConst170));
		fConst373 = (2.0f * (0.935140193f - fConst357));
		fConst374 = (1.0f / (((fConst178 + 0.157482162f) / fConst177) + 0.935140193f));
		fConst375 = (50.0638084f / fConst180);
		fConst376 = (fConst375 + 0.935140193f);
		fConst377 = (1.0f / (((fConst178 + 0.743130445f) / fConst177) + 1.4500711f));
		fConst378 = (11.0520525f / fConst180);
		fConst379 = (fConst378 + 1.4500711f);
		fConst380 = (1.0f / (((fConst178 + 3.18972731f) / fConst177) + 4.07678175f));
		fConst381 = (0.00176617282f / fConst180);
		fConst382 = (fConst381 + 0.000407678192f);
		fConst383 = (((fConst178 + -3.18972731f) / fConst177) + 4.07678175f);
		fConst384 = (2.0f * (4.07678175f - fConst181));
		fConst385 = (2.0f * (0.000407678192f - fConst381));
		fConst386 = (((fConst178 + -0.743130445f) / fConst177) + 1.4500711f);
		fConst387 = (2.0f * (1.4500711f - fConst181));
		fConst388 = (2.0f * (1.4500711f - fConst378));
		fConst389 = (((fConst178 + -0.157482162f) / fConst177) + 0.935140193f);
		fConst390 = (2.0f * (0.935140193f - fConst181));
		fConst391 = (2.0f * (0.935140193f - fConst375));
		fConst392 = (1.0f / (((fConst189 + 0.157482162f) / fConst188) + 0.935140193f));
		fConst393 = (50.0638084f / fConst191);
		fConst394 = (fConst393 + 0.935140193f);
		fConst395 = (1.0f / (((fConst189 + 0.743130445f) / fConst188) + 1.4500711f));
		fConst396 = (11.0520525f / fConst191);
		fConst397 = (fConst396 + 1.4500711f);
		fConst398 = (1.0f / (((fConst189 + 3.18972731f) / fConst188) + 4.07678175f));
		fConst399 = (0.00176617282f / fConst191);
		fConst400 = (fConst399 + 0.000407678192f);
		fConst401 = (((fConst189 + -3.18972731f) / fConst188) + 4.07678175f);
		fConst402 = (2.0f * (4.07678175f - fConst192));
		fConst403 = (2.0f * (0.000407678192f - fConst399));
		fConst404 = (((fConst189 + -0.743130445f) / fConst188) + 1.4500711f);
		fConst405 = (2.0f * (1.4500711f - fConst192));
		fConst406 = (2.0f * (1.4500711f - fConst396));
		fConst407 = (((fConst189 + -0.157482162f) / fConst188) + 0.935140193f);
		fConst408 = (2.0f * (0.935140193f - fConst192));
		fConst409 = (2.0f * (0.935140193f - fConst393));
		fConst410 = (1.0f / (((fConst26 + 0.157482162f) / fConst25) + 0.935140193f));
		fConst411 = (50.0638084f / fConst28);
		fConst412 = (fConst411 + 0.935140193f);
		fConst413 = (1.0f / (((fConst26 + 0.743130445f) / fConst25) + 1.4500711f));
		fConst414 = (11.0520525f / fConst28);
		fConst415 = (fConst414 + 1.4500711f);
		fConst416 = (1.0f / (((fConst26 + 3.18972731f) / fConst25) + 4.07678175f));
		fConst417 = (0.00176617282f / fConst28);
		fConst418 = (fConst417 + 0.000407678192f);
		fConst419 = (((fConst26 + -3.18972731f) / fConst25) + 4.07678175f);
		fConst420 = (2.0f * (4.07678175f - fConst29));
		fConst421 = (2.0f * (0.000407678192f - fConst417));
		fConst422 = (((fConst26 + -0.743130445f) / fConst25) + 1.4500711f);
		fConst423 = (2.0f * (1.4500711f - fConst29));
		fConst424 = (2.0f * (1.4500711f - fConst414));
		fConst425 = (((fConst26 + -0.157482162f) / fConst25) + 0.935140193f);
		fConst426 = (2.0f * (0.935140193f - fConst29));
		fConst427 = (2.0f * (0.935140193f - fConst411));
		fConst428 = (1.0f / (((fConst37 + 0.157482162f) / fConst36) + 0.935140193f));
		fConst429 = (50.0638084f / fConst39);
		fConst430 = (fConst429 + 0.935140193f);
		fConst431 = (1.0f / (((fConst37 + 0.743130445f) / fConst36) + 1.4500711f));
		fConst432 = (11.0520525f / fConst39);
		fConst433 = (fConst432 + 1.4500711f);
		fConst434 = (1.0f / (((fConst37 + 3.18972731f) / fConst36) + 4.07678175f));
		fConst435 = (0.00176617282f / fConst39);
		fConst436 = (fConst435 + 0.000407678192f);
		fConst437 = (((fConst37 + -3.18972731f) / fConst36) + 4.07678175f);
		fConst438 = (2.0f * (4.07678175f - fConst40));
		fConst439 = (2.0f * (0.000407678192f - fConst435));
		fConst440 = (((fConst37 + -0.743130445f) / fConst36) + 1.4500711f);
		fConst441 = (2.0f * (1.4500711f - fConst40));
		fConst442 = (2.0f * (1.4500711f - fConst432));
		fConst443 = (((fConst37 + -0.157482162f) / fConst36) + 0.935140193f);
		fConst444 = (2.0f * (0.935140193f - fConst40));
		fConst445 = (2.0f * (0.935140193f - fConst429));
		fConst446 = (1.0f / (((fConst48 + 0.157482162f) / fConst47) + 0.935140193f));
		fConst447 = (50.0638084f / fConst50);
		fConst448 = (fConst447 + 0.935140193f);
		fConst449 = (1.0f / (((fConst48 + 0.743130445f) / fConst47) + 1.4500711f));
		fConst450 = (11.0520525f / fConst50);
		fConst451 = (fConst450 + 1.4500711f);
		fConst452 = (1.0f / (((fConst48 + 3.18972731f) / fConst47) + 4.07678175f));
		fConst453 = (0.00176617282f / fConst50);
		fConst454 = (fConst453 + 0.000407678192f);
		fConst455 = (((fConst48 + -3.18972731f) / fConst47) + 4.07678175f);
		fConst456 = (2.0f * (4.07678175f - fConst51));
		fConst457 = (2.0f * (0.000407678192f - fConst453));
		fConst458 = (((fConst48 + -0.743130445f) / fConst47) + 1.4500711f);
		fConst459 = (2.0f * (1.4500711f - fConst51));
		fConst460 = (2.0f * (1.4500711f - fConst450));
		fConst461 = (((fConst48 + -0.157482162f) / fConst47) + 0.935140193f);
		fConst462 = (2.0f * (0.935140193f - fConst51));
		fConst463 = (2.0f * (0.935140193f - fConst447));
		fConst464 = (1.0f / (((fConst59 + 0.157482162f) / fConst58) + 0.935140193f));
		fConst465 = (50.0638084f / fConst61);
		fConst466 = (fConst465 + 0.935140193f);
		fConst467 = (1.0f / (((fConst59 + 0.743130445f) / fConst58) + 1.4500711f));
		fConst468 = (11.0520525f / fConst61);
		fConst469 = (fConst468 + 1.4500711f);
		fConst470 = (1.0f / (((fConst59 + 3.18972731f) / fConst58) + 4.07678175f));
		fConst471 = (0.00176617282f / fConst61);
		fConst472 = (fConst471 + 0.000407678192f);
		fConst473 = (((fConst59 + -3.18972731f) / fConst58) + 4.07678175f);
		fConst474 = (2.0f * (4.07678175f - fConst62));
		fConst475 = (2.0f * (0.000407678192f - fConst471));
		fConst476 = (2.0f * (1.4500711f - fConst62));
		fConst477 = (((fConst59 + -0.743130445f) / fConst58) + 1.4500711f);
		fConst478 = (2.0f * (1.4500711f - fConst468));
		fConst479 = (((fConst59 + -0.157482162f) / fConst58) + 0.935140193f);
		fConst480 = (2.0f * (0.935140193f - fConst62));
		fConst481 = (2.0f * (0.935140193f - fConst465));
		fConst482 = (1.0f / (((fConst200 + 0.157482162f) / fConst199) + 0.935140193f));
		fConst483 = (50.0638084f / fConst202);
		fConst484 = (2.0f * (0.935140193f - fConst483));
		fConst485 = (1.0f / (((fConst200 + 0.743130445f) / fConst199) + 1.4500711f));
		fConst486 = (11.0520525f / fConst202);
		fConst487 = (2.0f * (1.4500711f - fConst486));
		fConst488 = (1.0f / (((fConst200 + 3.18972731f) / fConst199) + 4.07678175f));
		fConst489 = (0.00176617282f / fConst202);
		fConst490 = (2.0f * (0.000407678192f - fConst489));
		fConst491 = (((fConst200 + -3.18972731f) / fConst199) + 4.07678175f);
		fConst492 = (2.0f * (4.07678175f - fConst203));
		fConst493 = (fConst489 + 0.000407678192f);
		fConst494 = (((fConst200 + -0.743130445f) / fConst199) + 1.4500711f);
		fConst495 = (2.0f * (1.4500711f - fConst203));
		fConst496 = (fConst486 + 1.4500711f);
		fConst497 = (((fConst200 + -0.157482162f) / fConst199) + 0.935140193f);
		fConst498 = (2.0f * (0.935140193f - fConst203));
		fConst499 = (fConst483 + 0.935140193f);
		fConst500 = (1.0f / (((fConst222 + 0.157482162f) / fConst221) + 0.935140193f));
		fConst501 = (50.0638084f / fConst224);
		fConst502 = (2.0f * (0.935140193f - fConst501));
		fConst503 = (1.0f / (((fConst222 + 0.743130445f) / fConst221) + 1.4500711f));
		fConst504 = (11.0520525f / fConst224);
		fConst505 = (2.0f * (1.4500711f - fConst504));
		fConst506 = (1.0f / (((fConst222 + 3.18972731f) / fConst221) + 4.07678175f));
		fConst507 = (0.00176617282f / fConst224);
		fConst508 = (2.0f * (0.000407678192f - fConst507));
		fConst509 = (((fConst222 + -3.18972731f) / fConst221) + 4.07678175f);
		fConst510 = (2.0f * (4.07678175f - fConst225));
		fConst511 = (fConst507 + 0.000407678192f);
		fConst512 = (((fConst222 + -0.743130445f) / fConst221) + 1.4500711f);
		fConst513 = (2.0f * (1.4500711f - fConst225));
		fConst514 = (fConst504 + 1.4500711f);
		fConst515 = (((fConst222 + -0.157482162f) / fConst221) + 0.935140193f);
		fConst516 = (2.0f * (0.935140193f - fConst225));
		fConst517 = (fConst501 + 0.935140193f);
		fConst518 = (1.0f / (((fConst211 + 0.157482162f) / fConst210) + 0.935140193f));
		fConst519 = (50.0638084f / fConst213);
		fConst520 = (2.0f * (0.935140193f - fConst519));
		fConst521 = (1.0f / (((fConst211 + 0.743130445f) / fConst210) + 1.4500711f));
		fConst522 = (11.0520525f / fConst213);
		fConst523 = (2.0f * (1.4500711f - fConst522));
		fConst524 = (1.0f / (((fConst211 + 3.18972731f) / fConst210) + 4.07678175f));
		fConst525 = (0.00176617282f / fConst213);
		fConst526 = (2.0f * (0.000407678192f - fConst525));
		fConst527 = (((fConst211 + -3.18972731f) / fConst210) + 4.07678175f);
		fConst528 = (2.0f * (4.07678175f - fConst214));
		fConst529 = (fConst525 + 0.000407678192f);
		fConst530 = (((fConst211 + -0.743130445f) / fConst210) + 1.4500711f);
		fConst531 = (2.0f * (1.4500711f - fConst214));
		fConst532 = (fConst522 + 1.4500711f);
		fConst533 = (((fConst211 + -0.157482162f) / fConst210) + 0.935140193f);
		fConst534 = (2.0f * (0.935140193f - fConst214));
		fConst535 = (fConst519 + 0.935140193f);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(50.0f);
		fHslider1 = FAUSTFLOAT(100.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(-20.0f);
		fHslider3 = FAUSTFLOAT(0.10000000000000001f);
		fHslider4 = FAUSTFLOAT(49.0f);
		fHslider5 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		
	}
	
	virtual void instanceClear() {
		for (int i0 = 0; (i0 < 2); i0 = (i0 + 1)) {
			iVec0[i0] = 0;
			
		}
		for (int i1 = 0; (i1 < 2); i1 = (i1 + 1)) {
			fRec20[i1] = 0.0f;
			
		}
		for (int i2 = 0; (i2 < 2); i2 = (i2 + 1)) {
			fRec23[i2] = 0.0f;
			
		}
		for (int i3 = 0; (i3 < 2); i3 = (i3 + 1)) {
			fRec21[i3] = 0.0f;
			
		}
		for (int i4 = 0; (i4 < 2); i4 = (i4 + 1)) {
			fRec22[i4] = 0.0f;
			
		}
		for (int i5 = 0; (i5 < 2); i5 = (i5 + 1)) {
			fRec24[i5] = 0.0f;
			
		}
		for (int i6 = 0; (i6 < 2); i6 = (i6 + 1)) {
			fRec25[i6] = 0.0f;
			
		}
		for (int i7 = 0; (i7 < 2); i7 = (i7 + 1)) {
			fVec1[i7] = 0.0f;
			
		}
		for (int i8 = 0; (i8 < 2); i8 = (i8 + 1)) {
			fRec19[i8] = 0.0f;
			
		}
		for (int i9 = 0; (i9 < 3); i9 = (i9 + 1)) {
			fRec18[i9] = 0.0f;
			
		}
		for (int i10 = 0; (i10 < 3); i10 = (i10 + 1)) {
			fRec17[i10] = 0.0f;
			
		}
		for (int i11 = 0; (i11 < 3); i11 = (i11 + 1)) {
			fRec16[i11] = 0.0f;
			
		}
		for (int i12 = 0; (i12 < 3); i12 = (i12 + 1)) {
			fRec15[i12] = 0.0f;
			
		}
		for (int i13 = 0; (i13 < 3); i13 = (i13 + 1)) {
			fRec14[i13] = 0.0f;
			
		}
		for (int i14 = 0; (i14 < 3); i14 = (i14 + 1)) {
			fRec13[i14] = 0.0f;
			
		}
		for (int i15 = 0; (i15 < 3); i15 = (i15 + 1)) {
			fRec12[i15] = 0.0f;
			
		}
		for (int i16 = 0; (i16 < 3); i16 = (i16 + 1)) {
			fRec11[i16] = 0.0f;
			
		}
		for (int i17 = 0; (i17 < 3); i17 = (i17 + 1)) {
			fRec10[i17] = 0.0f;
			
		}
		for (int i18 = 0; (i18 < 3); i18 = (i18 + 1)) {
			fRec9[i18] = 0.0f;
			
		}
		for (int i19 = 0; (i19 < 3); i19 = (i19 + 1)) {
			fRec8[i19] = 0.0f;
			
		}
		for (int i20 = 0; (i20 < 3); i20 = (i20 + 1)) {
			fRec7[i20] = 0.0f;
			
		}
		for (int i21 = 0; (i21 < 3); i21 = (i21 + 1)) {
			fRec6[i21] = 0.0f;
			
		}
		for (int i22 = 0; (i22 < 3); i22 = (i22 + 1)) {
			fRec5[i22] = 0.0f;
			
		}
		for (int i23 = 0; (i23 < 3); i23 = (i23 + 1)) {
			fRec4[i23] = 0.0f;
			
		}
		for (int i24 = 0; (i24 < 3); i24 = (i24 + 1)) {
			fRec3[i24] = 0.0f;
			
		}
		for (int i25 = 0; (i25 < 3); i25 = (i25 + 1)) {
			fRec2[i25] = 0.0f;
			
		}
		for (int i26 = 0; (i26 < 3); i26 = (i26 + 1)) {
			fRec1[i26] = 0.0f;
			
		}
		for (int i27 = 0; (i27 < 2); i27 = (i27 + 1)) {
			fRec0[i27] = 0.0f;
			
		}
		for (int i28 = 0; (i28 < 3); i28 = (i28 + 1)) {
			fRec29[i28] = 0.0f;
			
		}
		for (int i29 = 0; (i29 < 3); i29 = (i29 + 1)) {
			fRec28[i29] = 0.0f;
			
		}
		for (int i30 = 0; (i30 < 3); i30 = (i30 + 1)) {
			fRec27[i30] = 0.0f;
			
		}
		for (int i31 = 0; (i31 < 2); i31 = (i31 + 1)) {
			fRec26[i31] = 0.0f;
			
		}
		for (int i32 = 0; (i32 < 3); i32 = (i32 + 1)) {
			fRec57[i32] = 0.0f;
			
		}
		for (int i33 = 0; (i33 < 3); i33 = (i33 + 1)) {
			fRec56[i33] = 0.0f;
			
		}
		for (int i34 = 0; (i34 < 3); i34 = (i34 + 1)) {
			fRec55[i34] = 0.0f;
			
		}
		for (int i35 = 0; (i35 < 3); i35 = (i35 + 1)) {
			fRec54[i35] = 0.0f;
			
		}
		for (int i36 = 0; (i36 < 3); i36 = (i36 + 1)) {
			fRec53[i36] = 0.0f;
			
		}
		for (int i37 = 0; (i37 < 3); i37 = (i37 + 1)) {
			fRec52[i37] = 0.0f;
			
		}
		for (int i38 = 0; (i38 < 3); i38 = (i38 + 1)) {
			fRec51[i38] = 0.0f;
			
		}
		for (int i39 = 0; (i39 < 3); i39 = (i39 + 1)) {
			fRec50[i39] = 0.0f;
			
		}
		for (int i40 = 0; (i40 < 3); i40 = (i40 + 1)) {
			fRec49[i40] = 0.0f;
			
		}
		for (int i41 = 0; (i41 < 3); i41 = (i41 + 1)) {
			fRec48[i41] = 0.0f;
			
		}
		for (int i42 = 0; (i42 < 3); i42 = (i42 + 1)) {
			fRec47[i42] = 0.0f;
			
		}
		for (int i43 = 0; (i43 < 3); i43 = (i43 + 1)) {
			fRec46[i43] = 0.0f;
			
		}
		for (int i44 = 0; (i44 < 3); i44 = (i44 + 1)) {
			fRec45[i44] = 0.0f;
			
		}
		for (int i45 = 0; (i45 < 3); i45 = (i45 + 1)) {
			fRec44[i45] = 0.0f;
			
		}
		for (int i46 = 0; (i46 < 3); i46 = (i46 + 1)) {
			fRec43[i46] = 0.0f;
			
		}
		for (int i47 = 0; (i47 < 3); i47 = (i47 + 1)) {
			fRec42[i47] = 0.0f;
			
		}
		for (int i48 = 0; (i48 < 3); i48 = (i48 + 1)) {
			fRec41[i48] = 0.0f;
			
		}
		for (int i49 = 0; (i49 < 3); i49 = (i49 + 1)) {
			fRec40[i49] = 0.0f;
			
		}
		for (int i50 = 0; (i50 < 3); i50 = (i50 + 1)) {
			fRec39[i50] = 0.0f;
			
		}
		for (int i51 = 0; (i51 < 3); i51 = (i51 + 1)) {
			fRec38[i51] = 0.0f;
			
		}
		for (int i52 = 0; (i52 < 3); i52 = (i52 + 1)) {
			fRec37[i52] = 0.0f;
			
		}
		for (int i53 = 0; (i53 < 3); i53 = (i53 + 1)) {
			fRec36[i53] = 0.0f;
			
		}
		for (int i54 = 0; (i54 < 3); i54 = (i54 + 1)) {
			fRec35[i54] = 0.0f;
			
		}
		for (int i55 = 0; (i55 < 3); i55 = (i55 + 1)) {
			fRec34[i55] = 0.0f;
			
		}
		for (int i56 = 0; (i56 < 3); i56 = (i56 + 1)) {
			fRec33[i56] = 0.0f;
			
		}
		for (int i57 = 0; (i57 < 3); i57 = (i57 + 1)) {
			fRec32[i57] = 0.0f;
			
		}
		for (int i58 = 0; (i58 < 3); i58 = (i58 + 1)) {
			fRec31[i58] = 0.0f;
			
		}
		for (int i59 = 0; (i59 < 2); i59 = (i59 + 1)) {
			fRec30[i59] = 0.0f;
			
		}
		for (int i60 = 0; (i60 < 3); i60 = (i60 + 1)) {
			fRec61[i60] = 0.0f;
			
		}
		for (int i61 = 0; (i61 < 3); i61 = (i61 + 1)) {
			fRec60[i61] = 0.0f;
			
		}
		for (int i62 = 0; (i62 < 3); i62 = (i62 + 1)) {
			fRec59[i62] = 0.0f;
			
		}
		for (int i63 = 0; (i63 < 2); i63 = (i63 + 1)) {
			fRec58[i63] = 0.0f;
			
		}
		for (int i64 = 0; (i64 < 3); i64 = (i64 + 1)) {
			fRec65[i64] = 0.0f;
			
		}
		for (int i65 = 0; (i65 < 3); i65 = (i65 + 1)) {
			fRec64[i65] = 0.0f;
			
		}
		for (int i66 = 0; (i66 < 3); i66 = (i66 + 1)) {
			fRec63[i66] = 0.0f;
			
		}
		for (int i67 = 0; (i67 < 2); i67 = (i67 + 1)) {
			fRec62[i67] = 0.0f;
			
		}
		for (int i68 = 0; (i68 < 3); i68 = (i68 + 1)) {
			fRec69[i68] = 0.0f;
			
		}
		for (int i69 = 0; (i69 < 3); i69 = (i69 + 1)) {
			fRec68[i69] = 0.0f;
			
		}
		for (int i70 = 0; (i70 < 3); i70 = (i70 + 1)) {
			fRec67[i70] = 0.0f;
			
		}
		for (int i71 = 0; (i71 < 2); i71 = (i71 + 1)) {
			fRec66[i71] = 0.0f;
			
		}
		for (int i72 = 0; (i72 < 3); i72 = (i72 + 1)) {
			fRec73[i72] = 0.0f;
			
		}
		for (int i73 = 0; (i73 < 3); i73 = (i73 + 1)) {
			fRec72[i73] = 0.0f;
			
		}
		for (int i74 = 0; (i74 < 3); i74 = (i74 + 1)) {
			fRec71[i74] = 0.0f;
			
		}
		for (int i75 = 0; (i75 < 2); i75 = (i75 + 1)) {
			fRec70[i75] = 0.0f;
			
		}
		for (int i76 = 0; (i76 < 3); i76 = (i76 + 1)) {
			fRec77[i76] = 0.0f;
			
		}
		for (int i77 = 0; (i77 < 3); i77 = (i77 + 1)) {
			fRec76[i77] = 0.0f;
			
		}
		for (int i78 = 0; (i78 < 3); i78 = (i78 + 1)) {
			fRec75[i78] = 0.0f;
			
		}
		for (int i79 = 0; (i79 < 2); i79 = (i79 + 1)) {
			fRec74[i79] = 0.0f;
			
		}
		for (int i80 = 0; (i80 < 3); i80 = (i80 + 1)) {
			fRec81[i80] = 0.0f;
			
		}
		for (int i81 = 0; (i81 < 3); i81 = (i81 + 1)) {
			fRec80[i81] = 0.0f;
			
		}
		for (int i82 = 0; (i82 < 3); i82 = (i82 + 1)) {
			fRec79[i82] = 0.0f;
			
		}
		for (int i83 = 0; (i83 < 2); i83 = (i83 + 1)) {
			fRec78[i83] = 0.0f;
			
		}
		for (int i84 = 0; (i84 < 3); i84 = (i84 + 1)) {
			fRec85[i84] = 0.0f;
			
		}
		for (int i85 = 0; (i85 < 3); i85 = (i85 + 1)) {
			fRec84[i85] = 0.0f;
			
		}
		for (int i86 = 0; (i86 < 3); i86 = (i86 + 1)) {
			fRec83[i86] = 0.0f;
			
		}
		for (int i87 = 0; (i87 < 2); i87 = (i87 + 1)) {
			fRec82[i87] = 0.0f;
			
		}
		for (int i88 = 0; (i88 < 3); i88 = (i88 + 1)) {
			fRec89[i88] = 0.0f;
			
		}
		for (int i89 = 0; (i89 < 3); i89 = (i89 + 1)) {
			fRec88[i89] = 0.0f;
			
		}
		for (int i90 = 0; (i90 < 3); i90 = (i90 + 1)) {
			fRec87[i90] = 0.0f;
			
		}
		for (int i91 = 0; (i91 < 2); i91 = (i91 + 1)) {
			fRec86[i91] = 0.0f;
			
		}
		for (int i92 = 0; (i92 < 3); i92 = (i92 + 1)) {
			fRec93[i92] = 0.0f;
			
		}
		for (int i93 = 0; (i93 < 3); i93 = (i93 + 1)) {
			fRec92[i93] = 0.0f;
			
		}
		for (int i94 = 0; (i94 < 3); i94 = (i94 + 1)) {
			fRec91[i94] = 0.0f;
			
		}
		for (int i95 = 0; (i95 < 2); i95 = (i95 + 1)) {
			fRec90[i95] = 0.0f;
			
		}
		for (int i96 = 0; (i96 < 3); i96 = (i96 + 1)) {
			fRec97[i96] = 0.0f;
			
		}
		for (int i97 = 0; (i97 < 3); i97 = (i97 + 1)) {
			fRec96[i97] = 0.0f;
			
		}
		for (int i98 = 0; (i98 < 3); i98 = (i98 + 1)) {
			fRec95[i98] = 0.0f;
			
		}
		for (int i99 = 0; (i99 < 2); i99 = (i99 + 1)) {
			fRec94[i99] = 0.0f;
			
		}
		for (int i100 = 0; (i100 < 3); i100 = (i100 + 1)) {
			fRec101[i100] = 0.0f;
			
		}
		for (int i101 = 0; (i101 < 3); i101 = (i101 + 1)) {
			fRec100[i101] = 0.0f;
			
		}
		for (int i102 = 0; (i102 < 3); i102 = (i102 + 1)) {
			fRec99[i102] = 0.0f;
			
		}
		for (int i103 = 0; (i103 < 2); i103 = (i103 + 1)) {
			fRec98[i103] = 0.0f;
			
		}
		for (int i104 = 0; (i104 < 3); i104 = (i104 + 1)) {
			fRec105[i104] = 0.0f;
			
		}
		for (int i105 = 0; (i105 < 3); i105 = (i105 + 1)) {
			fRec104[i105] = 0.0f;
			
		}
		for (int i106 = 0; (i106 < 3); i106 = (i106 + 1)) {
			fRec103[i106] = 0.0f;
			
		}
		for (int i107 = 0; (i107 < 2); i107 = (i107 + 1)) {
			fRec102[i107] = 0.0f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "1", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "Sine oscillator based on 2D vector rotation");
		ui_interface->openVerticalBox("SINE WAVE OSCILLATOR oscrs");
		ui_interface->declare(&fHslider2, "1", "");
		ui_interface->declare(&fHslider2, "tooltip", "Sawtooth waveform amplitude");
		ui_interface->declare(&fHslider2, "unit", "dB");
		ui_interface->addHorizontalSlider("Amplitude", &fHslider2, -20.0f, -120.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fHslider4, "2", "");
		ui_interface->declare(&fHslider4, "tooltip", "Sine wave frequency as a Piano Key (PK) number (A440 = 49 PK)");
		ui_interface->declare(&fHslider4, "unit", "PK");
		ui_interface->addHorizontalSlider("Frequency", &fHslider4, 49.0f, 1.0f, 88.0f, 0.00999999978f);
		ui_interface->declare(&fHslider3, "3", "");
		ui_interface->declare(&fHslider3, "scale", "log");
		ui_interface->declare(&fHslider3, "tooltip", "Portamento (frequency-glide) time-constant in seconds");
		ui_interface->declare(&fHslider3, "unit", "sec");
		ui_interface->addHorizontalSlider("Portamento", &fHslider3, 0.100000001f, 0.00100000005f, 10.0f, 0.00100000005f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "tooltip", "Reference:          https://ccrma.stanford.edu/~jos/pasp/Cubic_Soft_Clipper.html");
		ui_interface->openVerticalBox("CUBIC NONLINEARITY cubicnl");
		ui_interface->declare(&fCheckbox0, "0", "");
		ui_interface->declare(&fCheckbox0, "tooltip", "When this is checked, the nonlinearity has no effect");
		ui_interface->addCheckButton("Bypass",&fCheckbox0);
		ui_interface->declare(&fHslider5, "1", "");
		ui_interface->declare(&fHslider5, "tooltip", "Amount of distortion");
		ui_interface->addHorizontalSlider("Drive", &fHslider5, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider6, "2", "");
		ui_interface->declare(&fHslider6, "tooltip", "Brings in even harmonics");
		ui_interface->addHorizontalSlider("Offset", &fHslider6, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openVerticalBox("0x00");
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "See Faust's filter.lib for documentation and references");
		ui_interface->openHorizontalBox("CONSTANT-Q SPECTRUM ANALYZER (6E), 15 bands spanning LP, 9 octaves below 16000 Hz, HP");
		ui_interface->declare(&fVbargraph2, "0", "");
		ui_interface->declare(&fVbargraph2, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph2, "unit", "dB");
        ui_interface->declare(&fVbargraph2, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c523a890", &fVbargraph2, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph3, "1", "");
		ui_interface->declare(&fVbargraph3, "tooltip", "Spectral Band Level in dB");
		ui_interface->declare(&fVbargraph3, "unit", "dB");
        ui_interface->declare(&fVbargraph3, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c524c000", &fVbargraph3, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph4, "2", "");
		ui_interface->declare(&fVbargraph4, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph4, "unit", "dB");
        ui_interface->declare(&fVbargraph4, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c525d820", &fVbargraph4, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph5, "3", "");
		ui_interface->declare(&fVbargraph5, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph5, "unit", "dB");
        ui_interface->declare(&fVbargraph5, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c526f0f0", &fVbargraph5, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph6, "4", "");
		ui_interface->declare(&fVbargraph6, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph6, "unit", "dB");
        ui_interface->declare(&fVbargraph6, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c5280a70", &fVbargraph6, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph7, "5", "");
		ui_interface->declare(&fVbargraph7, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph7, "unit", "dB");
        ui_interface->declare(&fVbargraph7, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c52924a0", &fVbargraph7, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph12, "6", "");
		ui_interface->declare(&fVbargraph12, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph12, "unit", "dB");
        ui_interface->declare(&fVbargraph12, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c52eb760", &fVbargraph12, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph14, "7", "");
		ui_interface->declare(&fVbargraph14, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph14, "unit", "dB");
        ui_interface->declare(&fVbargraph14, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c5312eb0", &fVbargraph14, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph13, "8", "");
		ui_interface->declare(&fVbargraph13, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph13, "unit", "dB");
        ui_interface->declare(&fVbargraph13, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c5301270", &fVbargraph13, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph0, "9", "");
		ui_interface->declare(&fVbargraph0, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph0, "unit", "dB");
        ui_interface->declare(&fVbargraph0, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c50969e0", &fVbargraph0, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph1, "10", "");
		ui_interface->declare(&fVbargraph1, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph1, "unit", "dB");
        ui_interface->declare(&fVbargraph1, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c50a80d0", &fVbargraph1, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph8, "11", "");
		ui_interface->declare(&fVbargraph8, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph8, "unit", "dB");
        ui_interface->declare(&fVbargraph8, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c52a3f80", &fVbargraph8, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph9, "12", "");
		ui_interface->declare(&fVbargraph9, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph9, "unit", "dB");
        ui_interface->declare(&fVbargraph9, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c52b5c70", &fVbargraph9, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph10, "13", "");
		ui_interface->declare(&fVbargraph10, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph10, "unit", "dB");
        ui_interface->declare(&fVbargraph10, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c52c7a10", &fVbargraph10, -50.0f, 10.0f);
		ui_interface->declare(&fVbargraph11, "14", "");
		ui_interface->declare(&fVbargraph11, "tooltip", "Spectral Band Level in dB");
        ui_interface->declare(&fVbargraph11, "unit", "dB");
        ui_interface->declare(&fVbargraph11, "style", "numerical");
		ui_interface->addVerticalBargraph("0x7fa9c52d9860", &fVbargraph11, -50.0f, 10.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("SPECTRUM ANALYZER CONTROLS");
		ui_interface->declare(&fHslider1, "0", "");
		ui_interface->declare(&fHslider1, "scale", "log");
		ui_interface->declare(&fHslider1, "tooltip", "band-level averaging time in milliseconds");
		ui_interface->declare(&fHslider1, "unit", "ms");
		ui_interface->addHorizontalSlider("Level Averaging Time", &fHslider1, 100.0f, 1.0f, 10000.0f, 1.0f);
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "tooltip", "Level offset in decibels");
		ui_interface->declare(&fHslider0, "unit", "dB");
		ui_interface->addHorizontalSlider("Level dB Offset", &fHslider0, 50.0f, 0.0f, 100.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->closeBox();
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = float(fHslider1);
		float fSlow2 = (((0.00100000005f * fSlow1) > 0.0f)?expf((0.0f - (fConst1 / fSlow1))):0.0f);
		int iSlow3 = int(float(fCheckbox0));
		float fSlow4 = (0.00100000005f * powf(10.0f, (0.0500000007f * float(fHslider2))));
		float fSlow5 = float(fHslider3);
		float fSlow6 = ((fSlow5 > 0.0f)?expf((0.0f - (fConst70 / fSlow5))):0.0f);
		float fSlow7 = ((440.0f * powf(2.0f, (0.0833333358f * (float(fHslider4) + -49.0f)))) * (1.0f - fSlow6));
		float fSlow8 = (0.00100000005f * float(fHslider5));
		float fSlow9 = (0.00100000005f * float(fHslider6));
		float fSlow10 = (1.0f - fSlow2);
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec20[0] = (fSlow4 + (0.999000013f * fRec20[1]));
			fRec23[0] = ((fSlow6 * fRec23[1]) + fSlow7);
			float fTemp0 = (fConst69 * fRec23[0]);
			float fTemp1 = sinf(fTemp0);
			float fTemp2 = cosf(fTemp0);
			fRec21[0] = ((fRec22[1] * fTemp1) + (fRec21[1] * fTemp2));
			fRec22[0] = (((fRec22[1] * fTemp2) + (fRec21[1] * (0.0f - fTemp1))) + float((1 - iVec0[1])));
			float fTemp3 = (fRec20[0] * fRec21[0]);
			fRec24[0] = (fSlow8 + (0.999000013f * fRec24[1]));
			fRec25[0] = (fSlow9 + (0.999000013f * fRec25[1]));
			float fTemp4 = max(-1.0f, min(1.0f, (((iSlow3?0.0f:fTemp3) * powf(10.0f, (2.0f * fRec24[0]))) + fRec25[0])));
			float fTemp5 = (fTemp4 * (1.0f - (0.333333343f * faustpower2_f(fTemp4))));
			fVec1[0] = fTemp5;
			fRec19[0] = (((0.995000005f * fRec19[1]) + fTemp5) - fVec1[1]);
			float fTemp6 = (iSlow3?fTemp3:fRec19[0]);
			fRec18[0] = (fTemp6 - (fConst66 * ((fConst71 * fRec18[2]) + (fConst72 * fRec18[1]))));
			fRec17[0] = ((fConst66 * ((fConst68 * (fRec18[2] + fRec18[0])) + (fConst73 * fRec18[1]))) - (fConst64 * ((fConst74 * fRec17[2]) + (fConst75 * fRec17[1]))));
			fRec16[0] = ((fConst64 * ((fConst65 * (fRec17[2] + fRec17[0])) + (fConst76 * fRec17[1]))) - (fConst60 * ((fConst77 * fRec16[2]) + (fConst78 * fRec16[1]))));
			float fTemp7 = (fConst60 * ((fConst63 * (fRec16[2] + fRec16[0])) + (fConst79 * fRec16[1])));
			fRec15[0] = (fTemp7 - (fConst55 * ((fConst80 * fRec15[2]) + (fConst81 * fRec15[1]))));
			fRec14[0] = ((fConst55 * ((fConst57 * (fRec15[2] + fRec15[0])) + (fConst82 * fRec15[1]))) - (fConst53 * ((fConst83 * fRec14[2]) + (fConst84 * fRec14[1]))));
			fRec13[0] = ((fConst53 * ((fConst54 * (fRec14[2] + fRec14[0])) + (fConst85 * fRec14[1]))) - (fConst49 * ((fConst86 * fRec13[2]) + (fConst87 * fRec13[1]))));
			float fTemp8 = (fConst49 * ((fConst52 * (fRec13[2] + fRec13[0])) + (fConst88 * fRec13[1])));
			fRec12[0] = (fTemp8 - (fConst44 * ((fConst89 * fRec12[2]) + (fConst90 * fRec12[1]))));
			fRec11[0] = ((fConst44 * ((fConst46 * (fRec12[2] + fRec12[0])) + (fConst91 * fRec12[1]))) - (fConst42 * ((fConst92 * fRec11[2]) + (fConst93 * fRec11[1]))));
			fRec10[0] = ((fConst42 * ((fConst43 * (fRec11[2] + fRec11[0])) + (fConst94 * fRec11[1]))) - (fConst38 * ((fConst95 * fRec10[2]) + (fConst96 * fRec10[1]))));
			float fTemp9 = (fConst38 * ((fConst41 * (fRec10[2] + fRec10[0])) + (fConst97 * fRec10[1])));
			fRec9[0] = (fTemp9 - (fConst33 * ((fConst98 * fRec9[2]) + (fConst99 * fRec9[1]))));
			fRec8[0] = ((fConst33 * ((fConst35 * (fRec9[2] + fRec9[0])) + (fConst100 * fRec9[1]))) - (fConst31 * ((fConst101 * fRec8[2]) + (fConst102 * fRec8[1]))));
			fRec7[0] = ((fConst31 * ((fConst32 * (fRec8[2] + fRec8[0])) + (fConst103 * fRec8[1]))) - (fConst27 * ((fConst104 * fRec7[2]) + (fConst105 * fRec7[1]))));
			float fTemp10 = (fConst27 * ((fConst30 * (fRec7[2] + fRec7[0])) + (fConst106 * fRec7[1])));
			fRec6[0] = (fTemp10 - (fConst22 * ((fConst107 * fRec6[2]) + (fConst108 * fRec6[1]))));
			fRec5[0] = ((fConst22 * ((fConst24 * (fRec6[2] + fRec6[0])) + (fConst109 * fRec6[1]))) - (fConst20 * ((fConst110 * fRec5[2]) + (fConst111 * fRec5[1]))));
			fRec4[0] = ((fConst20 * ((fConst21 * (fRec5[2] + fRec5[0])) + (fConst112 * fRec5[1]))) - (fConst16 * ((fConst113 * fRec4[2]) + (fConst114 * fRec4[1]))));
			float fTemp11 = (fConst16 * ((fConst19 * (fRec4[2] + fRec4[0])) + (fConst115 * fRec4[1])));
			fRec3[0] = (fTemp11 - (fConst11 * ((fConst116 * fRec3[2]) + (fConst118 * fRec3[1]))));
			fRec2[0] = ((fConst11 * ((fConst13 * (fRec3[2] + fRec3[0])) + (fConst119 * fRec3[1]))) - (fConst8 * ((fConst120 * fRec2[2]) + (fConst121 * fRec2[1]))));
			fRec1[0] = ((fConst8 * ((fConst10 * (fRec2[2] + fRec2[0])) + (fConst122 * fRec2[1]))) - (fConst4 * ((fConst123 * fRec1[2]) + (fConst124 * fRec1[1]))));
			fRec0[0] = ((fSlow2 * fRec0[1]) + (fabsf((fConst4 * ((fConst7 * (fRec1[2] + fRec1[0])) + (fConst125 * fRec1[1])))) * fSlow10));
			fVbargraph0 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec0[0]))));
			fRec29[0] = (fTemp10 - (fConst132 * ((fConst135 * fRec29[2]) + (fConst136 * fRec29[1]))));
			fRec28[0] = ((fConst132 * ((fConst134 * (fRec29[2] + fRec29[0])) + (fConst137 * fRec29[1]))) - (fConst129 * ((fConst138 * fRec28[2]) + (fConst139 * fRec28[1]))));
			fRec27[0] = ((fConst129 * ((fConst131 * (fRec28[2] + fRec28[0])) + (fConst140 * fRec28[1]))) - (fConst126 * ((fConst141 * fRec27[2]) + (fConst142 * fRec27[1]))));
			fRec26[0] = ((fSlow2 * fRec26[1]) + (fabsf((fConst126 * ((fConst128 * (fRec27[2] + fRec27[0])) + (fConst143 * fRec27[1])))) * fSlow10));
			fVbargraph1 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec26[0]))));
			fRec57[0] = (fTemp11 - (fConst236 * ((fConst239 * fRec57[2]) + (fConst240 * fRec57[1]))));
			fRec56[0] = ((fConst236 * ((fConst238 * (fRec57[2] + fRec57[0])) + (fConst241 * fRec57[1]))) - (fConst234 * ((fConst242 * fRec56[2]) + (fConst243 * fRec56[1]))));
			fRec55[0] = ((fConst234 * ((fConst235 * (fRec56[2] + fRec56[0])) + (fConst244 * fRec56[1]))) - (fConst232 * ((fConst245 * fRec55[2]) + (fConst246 * fRec55[1]))));
			float fTemp12 = (fConst232 * ((fConst233 * (fRec55[2] + fRec55[0])) + (fConst247 * fRec55[1])));
			fRec54[0] = (fTemp12 - (fConst229 * ((fConst248 * fRec54[2]) + (fConst249 * fRec54[1]))));
			fRec53[0] = ((fConst229 * ((fConst231 * (fRec54[2] + fRec54[0])) + (fConst250 * fRec54[1]))) - (fConst227 * ((fConst251 * fRec53[2]) + (fConst252 * fRec53[1]))));
			fRec52[0] = ((fConst227 * ((fConst228 * (fRec53[2] + fRec53[0])) + (fConst253 * fRec53[1]))) - (fConst223 * ((fConst254 * fRec52[2]) + (fConst255 * fRec52[1]))));
			float fTemp13 = (fConst223 * ((fConst226 * (fRec52[2] + fRec52[0])) + (fConst256 * fRec52[1])));
			fRec51[0] = (fTemp13 - (fConst218 * ((fConst257 * fRec51[2]) + (fConst258 * fRec51[1]))));
			fRec50[0] = ((fConst218 * ((fConst220 * (fRec51[2] + fRec51[0])) + (fConst259 * fRec51[1]))) - (fConst216 * ((fConst260 * fRec50[2]) + (fConst261 * fRec50[1]))));
			fRec49[0] = ((fConst216 * ((fConst217 * (fRec50[2] + fRec50[0])) + (fConst262 * fRec50[1]))) - (fConst212 * ((fConst263 * fRec49[2]) + (fConst264 * fRec49[1]))));
			float fTemp14 = (fConst212 * ((fConst215 * (fRec49[2] + fRec49[0])) + (fConst265 * fRec49[1])));
			fRec48[0] = (fTemp14 - (fConst207 * ((fConst266 * fRec48[2]) + (fConst267 * fRec48[1]))));
			fRec47[0] = ((fConst207 * ((fConst209 * (fRec48[2] + fRec48[0])) + (fConst268 * fRec48[1]))) - (fConst205 * ((fConst269 * fRec47[2]) + (fConst270 * fRec47[1]))));
			fRec46[0] = ((fConst205 * ((fConst206 * (fRec47[2] + fRec47[0])) + (fConst271 * fRec47[1]))) - (fConst201 * ((fConst272 * fRec46[2]) + (fConst273 * fRec46[1]))));
			float fTemp15 = (fConst201 * ((fConst204 * (fRec46[2] + fRec46[0])) + (fConst274 * fRec46[1])));
			fRec45[0] = (fTemp15 - (fConst196 * ((fConst275 * fRec45[2]) + (fConst276 * fRec45[1]))));
			fRec44[0] = ((fConst196 * ((fConst198 * (fRec45[2] + fRec45[0])) + (fConst277 * fRec45[1]))) - (fConst194 * ((fConst278 * fRec44[2]) + (fConst279 * fRec44[1]))));
			fRec43[0] = ((fConst194 * ((fConst195 * (fRec44[2] + fRec44[0])) + (fConst280 * fRec44[1]))) - (fConst190 * ((fConst281 * fRec43[2]) + (fConst282 * fRec43[1]))));
			float fTemp16 = (fConst190 * ((fConst193 * (fRec43[2] + fRec43[0])) + (fConst283 * fRec43[1])));
			fRec42[0] = (fTemp16 - (fConst185 * ((fConst284 * fRec42[2]) + (fConst285 * fRec42[1]))));
			fRec41[0] = ((fConst185 * ((fConst187 * (fRec42[2] + fRec42[0])) + (fConst286 * fRec42[1]))) - (fConst183 * ((fConst287 * fRec41[2]) + (fConst288 * fRec41[1]))));
			fRec40[0] = ((fConst183 * ((fConst184 * (fRec41[2] + fRec41[0])) + (fConst289 * fRec41[1]))) - (fConst179 * ((fConst290 * fRec40[2]) + (fConst291 * fRec40[1]))));
			float fTemp17 = (fConst179 * ((fConst182 * (fRec40[2] + fRec40[0])) + (fConst292 * fRec40[1])));
			fRec39[0] = (fTemp17 - (fConst174 * ((fConst293 * fRec39[2]) + (fConst294 * fRec39[1]))));
			fRec38[0] = ((fConst174 * ((fConst176 * (fRec39[2] + fRec39[0])) + (fConst295 * fRec39[1]))) - (fConst172 * ((fConst296 * fRec38[2]) + (fConst297 * fRec38[1]))));
			fRec37[0] = ((fConst172 * ((fConst173 * (fRec38[2] + fRec38[0])) + (fConst298 * fRec38[1]))) - (fConst168 * ((fConst299 * fRec37[2]) + (fConst300 * fRec37[1]))));
			float fTemp18 = (fConst168 * ((fConst171 * (fRec37[2] + fRec37[0])) + (fConst301 * fRec37[1])));
			fRec36[0] = (fTemp18 - (fConst163 * ((fConst302 * fRec36[2]) + (fConst303 * fRec36[1]))));
			fRec35[0] = ((fConst163 * ((fConst165 * (fRec36[2] + fRec36[0])) + (fConst304 * fRec36[1]))) - (fConst161 * ((fConst305 * fRec35[2]) + (fConst306 * fRec35[1]))));
			fRec34[0] = ((fConst161 * ((fConst162 * (fRec35[2] + fRec35[0])) + (fConst307 * fRec35[1]))) - (fConst157 * ((fConst308 * fRec34[2]) + (fConst309 * fRec34[1]))));
			float fTemp19 = (fConst157 * ((fConst160 * (fRec34[2] + fRec34[0])) + (fConst310 * fRec34[1])));
			fRec33[0] = (fTemp19 - (fConst152 * ((fConst311 * fRec33[2]) + (fConst312 * fRec33[1]))));
			fRec32[0] = ((fConst152 * ((fConst154 * (fRec33[2] + fRec33[0])) + (fConst313 * fRec33[1]))) - (fConst150 * ((fConst314 * fRec32[2]) + (fConst315 * fRec32[1]))));
			fRec31[0] = ((fConst150 * ((fConst151 * (fRec32[2] + fRec32[0])) + (fConst316 * fRec32[1]))) - (fConst146 * ((fConst317 * fRec31[2]) + (fConst318 * fRec31[1]))));
			fRec30[0] = ((fSlow2 * fRec30[1]) + (fabsf((fConst146 * ((fConst149 * (fRec31[2] + fRec31[0])) + (fConst319 * fRec31[1])))) * fSlow10));
			fVbargraph2 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec30[0]))));
			fRec61[0] = (fTemp19 - (fConst326 * ((fConst329 * fRec61[2]) + (fConst330 * fRec61[1]))));
			fRec60[0] = ((fConst326 * ((fConst328 * (fRec61[2] + fRec61[0])) + (fConst331 * fRec61[1]))) - (fConst323 * ((fConst332 * fRec60[2]) + (fConst333 * fRec60[1]))));
			fRec59[0] = ((fConst323 * ((fConst325 * (fRec60[2] + fRec60[0])) + (fConst334 * fRec60[1]))) - (fConst320 * ((fConst335 * fRec59[2]) + (fConst336 * fRec59[1]))));
			fRec58[0] = ((fabsf((fConst320 * ((fConst322 * (fRec59[2] + fRec59[0])) + (fConst337 * fRec59[1])))) * fSlow10) + (fSlow2 * fRec58[1]));
			fVbargraph3 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec58[0]))));
			fRec65[0] = (fTemp18 - (fConst344 * ((fConst347 * fRec65[2]) + (fConst348 * fRec65[1]))));
			fRec64[0] = ((fConst344 * ((fConst346 * (fRec65[2] + fRec65[0])) + (fConst349 * fRec65[1]))) - (fConst341 * ((fConst350 * fRec64[2]) + (fConst351 * fRec64[1]))));
			fRec63[0] = ((fConst341 * ((fConst343 * (fRec64[2] + fRec64[0])) + (fConst352 * fRec64[1]))) - (fConst338 * ((fConst353 * fRec63[2]) + (fConst354 * fRec63[1]))));
			fRec62[0] = ((fSlow2 * fRec62[1]) + (fSlow10 * fabsf((fConst338 * ((fConst340 * (fRec63[2] + fRec63[0])) + (fConst355 * fRec63[1]))))));
			fVbargraph4 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec62[0]))));
			fRec69[0] = (fTemp17 - (fConst362 * ((fConst365 * fRec69[2]) + (fConst366 * fRec69[1]))));
			fRec68[0] = ((fConst362 * ((fConst364 * (fRec69[2] + fRec69[0])) + (fConst367 * fRec69[1]))) - (fConst359 * ((fConst368 * fRec68[2]) + (fConst369 * fRec68[1]))));
			fRec67[0] = ((fConst359 * ((fConst361 * (fRec68[2] + fRec68[0])) + (fConst370 * fRec68[1]))) - (fConst356 * ((fConst371 * fRec67[2]) + (fConst372 * fRec67[1]))));
			fRec66[0] = ((fSlow2 * fRec66[1]) + (fSlow10 * fabsf((fConst356 * ((fConst358 * (fRec67[2] + fRec67[0])) + (fConst373 * fRec67[1]))))));
			fVbargraph5 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec66[0]))));
			fRec73[0] = (fTemp16 - (fConst380 * ((fConst383 * fRec73[2]) + (fConst384 * fRec73[1]))));
			fRec72[0] = ((fConst380 * ((fConst382 * (fRec73[2] + fRec73[0])) + (fConst385 * fRec73[1]))) - (fConst377 * ((fConst386 * fRec72[2]) + (fConst387 * fRec72[1]))));
			fRec71[0] = ((fConst377 * ((fConst379 * (fRec72[2] + fRec72[0])) + (fConst388 * fRec72[1]))) - (fConst374 * ((fConst389 * fRec71[2]) + (fConst390 * fRec71[1]))));
			fRec70[0] = ((fSlow2 * fRec70[1]) + (fSlow10 * fabsf((fConst374 * ((fConst376 * (fRec71[2] + fRec71[0])) + (fConst391 * fRec71[1]))))));
			fVbargraph6 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec70[0]))));
			fRec77[0] = (fTemp15 - (fConst398 * ((fConst401 * fRec77[2]) + (fConst402 * fRec77[1]))));
			fRec76[0] = ((fConst398 * ((fConst400 * (fRec77[2] + fRec77[0])) + (fConst403 * fRec77[1]))) - (fConst395 * ((fConst404 * fRec76[2]) + (fConst405 * fRec76[1]))));
			fRec75[0] = ((fConst395 * ((fConst397 * (fRec76[2] + fRec76[0])) + (fConst406 * fRec76[1]))) - (fConst392 * ((fConst407 * fRec75[2]) + (fConst408 * fRec75[1]))));
			fRec74[0] = ((fSlow2 * fRec74[1]) + (fSlow10 * fabsf((fConst392 * ((fConst394 * (fRec75[2] + fRec75[0])) + (fConst409 * fRec75[1]))))));
			fVbargraph7 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec74[0]))));
			fRec81[0] = (fTemp9 - (fConst416 * ((fConst419 * fRec81[2]) + (fConst420 * fRec81[1]))));
			fRec80[0] = ((fConst416 * ((fConst418 * (fRec81[2] + fRec81[0])) + (fConst421 * fRec81[1]))) - (fConst413 * ((fConst422 * fRec80[2]) + (fConst423 * fRec80[1]))));
			fRec79[0] = ((fConst413 * ((fConst415 * (fRec80[2] + fRec80[0])) + (fConst424 * fRec80[1]))) - (fConst410 * ((fConst425 * fRec79[2]) + (fConst426 * fRec79[1]))));
			fRec78[0] = ((fSlow2 * fRec78[1]) + (fSlow10 * fabsf((fConst410 * ((fConst412 * (fRec79[2] + fRec79[0])) + (fConst427 * fRec79[1]))))));
			fVbargraph8 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec78[0]))));
			fRec85[0] = (fTemp8 - (fConst434 * ((fConst437 * fRec85[2]) + (fConst438 * fRec85[1]))));
			fRec84[0] = ((fConst434 * ((fConst436 * (fRec85[2] + fRec85[0])) + (fConst439 * fRec85[1]))) - (fConst431 * ((fConst440 * fRec84[2]) + (fConst441 * fRec84[1]))));
			fRec83[0] = ((fConst431 * ((fConst433 * (fRec84[2] + fRec84[0])) + (fConst442 * fRec84[1]))) - (fConst428 * ((fConst443 * fRec83[2]) + (fConst444 * fRec83[1]))));
			fRec82[0] = ((fSlow2 * fRec82[1]) + (fSlow10 * fabsf((fConst428 * ((fConst430 * (fRec83[2] + fRec83[0])) + (fConst445 * fRec83[1]))))));
			fVbargraph9 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec82[0]))));
			fRec89[0] = (fTemp7 - (fConst452 * ((fConst455 * fRec89[2]) + (fConst456 * fRec89[1]))));
			fRec88[0] = ((fConst452 * ((fConst454 * (fRec89[2] + fRec89[0])) + (fConst457 * fRec89[1]))) - (fConst449 * ((fConst458 * fRec88[2]) + (fConst459 * fRec88[1]))));
			fRec87[0] = ((fConst449 * ((fConst451 * (fRec88[2] + fRec88[0])) + (fConst460 * fRec88[1]))) - (fConst446 * ((fConst461 * fRec87[2]) + (fConst462 * fRec87[1]))));
			fRec86[0] = ((fSlow2 * fRec86[1]) + (fSlow10 * fabsf((fConst446 * ((fConst448 * (fRec87[2] + fRec87[0])) + (fConst463 * fRec87[1]))))));
			fVbargraph10 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec86[0]))));
			fRec93[0] = (fTemp6 - (fConst470 * ((fConst473 * fRec93[2]) + (fConst474 * fRec93[1]))));
			fRec92[0] = ((fConst470 * ((fConst472 * (fRec93[2] + fRec93[0])) + (fConst475 * fRec93[1]))) - (fConst467 * ((fConst476 * fRec92[1]) + (fConst477 * fRec92[2]))));
			fRec91[0] = ((fConst467 * ((fConst469 * (fRec92[2] + fRec92[0])) + (fConst478 * fRec92[1]))) - (fConst464 * ((fConst479 * fRec91[2]) + (fConst480 * fRec91[1]))));
			fRec90[0] = ((fSlow2 * fRec90[1]) + (fSlow10 * fabsf((fConst464 * ((fConst466 * (fRec91[2] + fRec91[0])) + (fConst481 * fRec91[1]))))));
			fVbargraph11 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec90[0]))));
			fRec97[0] = (fTemp14 - (fConst488 * ((fConst491 * fRec97[2]) + (fConst492 * fRec97[1]))));
			fRec96[0] = ((fConst488 * ((fConst490 * fRec97[1]) + (fConst493 * (fRec97[2] + fRec97[0])))) - (fConst485 * ((fConst494 * fRec96[2]) + (fConst495 * fRec96[1]))));
			fRec95[0] = ((fConst485 * ((fConst487 * fRec96[1]) + (fConst496 * (fRec96[2] + fRec96[0])))) - (fConst482 * ((fConst497 * fRec95[2]) + (fConst498 * fRec95[1]))));
			fRec94[0] = ((fRec94[1] * fSlow2) + (fSlow10 * fabsf((fConst482 * ((fConst484 * fRec95[1]) + (fConst499 * (fRec95[2] + fRec95[0])))))));
			fVbargraph12 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec94[0]))));
			fRec101[0] = (fTemp12 - (fConst506 * ((fConst509 * fRec101[2]) + (fConst510 * fRec101[1]))));
			fRec100[0] = ((fConst506 * ((fConst508 * fRec101[1]) + (fConst511 * (fRec101[2] + fRec101[0])))) - (fConst503 * ((fConst512 * fRec100[2]) + (fConst513 * fRec100[1]))));
			fRec99[0] = ((fConst503 * ((fConst505 * fRec100[1]) + (fConst514 * (fRec100[2] + fRec100[0])))) - (fConst500 * ((fConst515 * fRec99[2]) + (fConst516 * fRec99[1]))));
			fRec98[0] = ((fSlow2 * fRec98[1]) + (fabsf((fConst500 * ((fConst502 * fRec99[1]) + (fConst517 * (fRec99[2] + fRec99[0]))))) * fSlow10));
			fVbargraph13 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec98[0]))));
			fRec105[0] = (fTemp13 - (fConst524 * ((fConst527 * fRec105[2]) + (fConst528 * fRec105[1]))));
			fRec104[0] = ((fConst524 * ((fConst526 * fRec105[1]) + (fConst529 * (fRec105[2] + fRec105[0])))) - (fConst521 * ((fConst530 * fRec104[2]) + (fConst531 * fRec104[1]))));
			fRec103[0] = ((fConst521 * ((fConst523 * fRec104[1]) + (fConst532 * (fRec104[2] + fRec104[0])))) - (fConst518 * ((fConst533 * fRec103[2]) + (fConst534 * fRec103[1]))));
			fRec102[0] = ((fRec102[1] * fSlow2) + (fabsf((fConst518 * ((fConst520 * fRec103[1]) + (fConst535 * (fRec103[2] + fRec103[0]))))) * fSlow10));
			fVbargraph14 = FAUSTFLOAT((fSlow0 + (20.0f * log10f(fRec102[0]))));
			output0[i] = FAUSTFLOAT(fTemp6);
			output1[i] = FAUSTFLOAT(fTemp6);
			iVec0[1] = iVec0[0];
			fRec20[1] = fRec20[0];
			fRec23[1] = fRec23[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fRec24[1] = fRec24[0];
			fRec25[1] = fRec25[0];
			fVec1[1] = fVec1[0];
			fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fRec27[2] = fRec27[1];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec30[1] = fRec30[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec58[1] = fRec58[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec62[1] = fRec62[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec66[1] = fRec66[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fRec70[1] = fRec70[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec74[1] = fRec74[0];
			fRec81[2] = fRec81[1];
			fRec81[1] = fRec81[0];
			fRec80[2] = fRec80[1];
			fRec80[1] = fRec80[0];
			fRec79[2] = fRec79[1];
			fRec79[1] = fRec79[0];
			fRec78[1] = fRec78[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec84[2] = fRec84[1];
			fRec84[1] = fRec84[0];
			fRec83[2] = fRec83[1];
			fRec83[1] = fRec83[0];
			fRec82[1] = fRec82[0];
			fRec89[2] = fRec89[1];
			fRec89[1] = fRec89[0];
			fRec88[2] = fRec88[1];
			fRec88[1] = fRec88[0];
			fRec87[2] = fRec87[1];
			fRec87[1] = fRec87[0];
			fRec86[1] = fRec86[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fRec92[2] = fRec92[1];
			fRec92[1] = fRec92[0];
			fRec91[2] = fRec91[1];
			fRec91[1] = fRec91[0];
			fRec90[1] = fRec90[0];
			fRec97[2] = fRec97[1];
			fRec97[1] = fRec97[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec95[2] = fRec95[1];
			fRec95[1] = fRec95[0];
			fRec94[1] = fRec94[0];
			fRec101[2] = fRec101[1];
			fRec101[1] = fRec101[0];
			fRec100[2] = fRec100[1];
			fRec100[1] = fRec100[0];
			fRec99[2] = fRec99[1];
			fRec99[1] = fRec99[0];
			fRec98[1] = fRec98[0];
			fRec105[2] = fRec105[1];
			fRec105[1] = fRec105[0];
			fRec104[2] = fRec104[1];
			fRec104[1] = fRec104[0];
			fRec103[2] = fRec103[1];
			fRec103[1] = fRec103[0];
			fRec102[1] = fRec102[0];
			
		}
		
	}

	
};


#endif
