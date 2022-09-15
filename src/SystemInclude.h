//#define	PULSERADAR26
#define	PULSERADAR6
//#define	GUIDERADAR

#ifdef PULSERADAR26
	#define	RF_FREQUENCY		22
#endif
#ifdef PULSERADAR6
	#define	RF_FREQUENCY		43
#endif
#ifdef GUIDERADAR
	#define	RF_FREQUENCY		16
#endif

#define	SYSTEMDISTANCE		20000
#define	TOTALSAMPLEDOT		1800
#define	CURVEMAXDOT			100
#define	ONE_DOT_MM			11.11
#define	ONE_MM_DOT			0.09