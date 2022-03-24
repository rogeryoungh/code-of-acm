\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{probook}[2021/03/16 v0.0.1 Program Document Class]

\LoadClass[a4paper,oneside,UTF8,fontset=none]{ctexbook}

%%%% pronote 设置

%% 数学环境

\RequirePackage{amsmath}
\RequirePackage{amsfonts}
\RequirePackage{amssymb}
\RequirePackage{mathtools}
\RequirePackage{mathrsfs}
\RequirePackage[xindy]{imakeidx}

%% 页面设置

\RequirePackage{geometry}
\geometry{
  a4paper,
  top=25.4mm, bottom=25.4mm,
  left=20mm, right=20mm,
  headheight=2.17cm,
  headsep=4mm,
  footskip=12mm
}
\pagestyle{plain}

%% 颜色

\RequirePackage[table]{xcolor}

\definecolor{linkcolor}{rgb}{0.5,0,0}
\definecolor{frenchplum}{RGB}{190,20,83}

%% 链接

\RequirePackage{hyperref}
\hypersetup{
	breaklinks,
	unicode,
	linktoc=all,
	bookmarksnumbered=true,
	bookmarksopen=true,
	pdfkeywords={proart},
	colorlinks,
	linkcolor=linkcolor,
	citecolor=linkcolor,
	urlcolor=linkcolor,
	plainpages=false,
	pdfstartview=FitH,
	pdfborder={0 0 0},
}

%% 目录

\ctexset{
	section/titleformat = \raggedright
}
\setcounter{secnumdepth}{3}
\setcounter{tocdepth}{3}



%% 字体

%\setCJKmainfont[BoldFont={FZHei-B01},ItalicFont={FZKai-Z03}]{FZShuSong-Z01}
%\setCJKsansfont{FZHei-B01}
%\setCJKfamilyfont{zhsong}{FZShuSong-Z01}
%\setCJKfamilyfont{zhhei}{FZHei-B01}
%\setCJKfamilyfont{zhbsong}{方正小标宋_GBK}
\setCJKmainfont[BoldFont={Noto Serif CJK SC Bold},ItalicFont={Noto Sans CJK SC}]{Noto Serif CJK SC}
\setCJKsansfont{Noto Sans CJK SC}
\setCJKmonofont{Sarasa Mono SC}
\setCJKfamilyfont{zhsong}{Noto Serif CJK SC}
\setCJKfamilyfont{zhhei}{Noto Sans CJK SC}
\setCJKfamilyfont{zhkai}{FZKai-Z03}
\setCJKfamilyfont{zhfs}{FZFangSong-Z02}
\setCJKfamilyfont{zhbsong}{Noto Serif CJK SC Bold}
\newcommand*{\fzsong}{\CJKfamily{zhsong}}
\newcommand*{\fzhei}{\CJKfamily{zhhei}}
\newcommand*{\fzkai}{\CJKfamily{zhkai}}
\newcommand*{\fzxbs}{\CJKfamily{zhbsong}}
\newcommand*{\fzfs}{\CJKfamily{zhfs}}

%% 代码

\RequirePackage{listings}
% \setmonofont{Sarasa Mono SC}
% \setmonofont{Sarasa Mono Slab SC}
\setmonofont{JetBrains Mono}

\definecolor{codecolorkeywords}{RGB}{0,96,255}
\definecolor{codecolorcomments}{RGB}{127,127,127}
\definecolor{codecolorxmlcomments}{rgb}{0.5,0.5,0.5}
\definecolor{codecolorstrings}{RGB}{83,160,119}
\definecolor{codecolortypes}{rgb}{0.17,0.57,0.68}
\definecolor{codecolorbg}{RGB}{244,247,248}

\lstset{basicstyle=\small\linespread{1.0}\ttfamily \lst@ifdisplaystyle\fi,
	% Code
	columns=fullflexible,
	tabsize=3,
	showspaces=false,
	showstringspaces=false,
	showtabs=false,
	breaklines=true,
	numbers=left,
	numbersep=10pt,
	xleftmargin=2em,
	stepnumber=1,
	firstnumber=1,
	numberfirstline=true,
	% Code design
	% keywordstyle=\bfseries\color{codecolorkeywords},
	% commentstyle=\color{codecolorcomments},
	% stringstyle=\color{codecolorstrings},
	% numberstyle=\ttfamily\small\color{gray},
	keywordstyle=\bfseries,
	commentstyle=\color{codecolorcomments},
	numberstyle=\ttfamily,
	breakatwhitespace=false,
	breaklines=true,
	captionpos=t,
	keepspaces=true,
	%frame
	frame=tb,
	framerule=.5pt,
	framexleftmargin=7mm,
	rulecolor=\color{black},
	%backgroundcolor=\color{codecolorbg},
	abovecaptionskip=0pt,
	belowcaptionskip=5pt,
}


\lstdefinestyle{cpp}{
	% Line numbers
	literate=
		{==}{{{=}{=}}}2
		{->}{{->}}2
		{!=}{{!=}}2
		{>=}{{>=}}2
		{<=}{{<=}}2
		{<>}{{<>}}2
		{>>}{{>>}}2
		{<<}{{<<}}2
		{\&\&}{{\&\&}}2,
	language=C++,
	morekeywords={sort,memset,swap,copy,memcpy,fill},
	emph={int,long,float,double,short,byte,bool,ll,signed,unsigned,void,char,true,false,vector,pair,stack,set,priority_queue,pii,i128},
	% emphstyle=\color{frenchplum},
	emphstyle=\bfseries,
}


\lstdefinestyle{python}{
	% Line numbers
	literate=
		{==}{{{=}{=}}}2
		{->}{{->}}2
		{!=}{{!=}}2
		{>=}{{>=}}2
		{<=}{{<=}}2
		{<>}{{<>}}2
		{>>}{{>>}}2
		{<<}{{<<}}2
		{\&\&}{{\&\&}}2,
	language=python,
}

\lstdefinestyle{nonumbers}{
	numbers=none,
	xleftmargin=1em,
	framexleftmargin=3.5mm,
}

\RequirePackage{caption}
\DeclareCaptionFormat{codecaptionformat}{%
	\parbox{\linewidth}{#1#2 \ttfamily#3}
}
\captionsetup[lstlisting]{format=codecaptionformat}
\renewcommand{\lstlistingname}{ {\ttfamily </> 代码}}

%% 定理环境

\RequirePackage{pifont,manfnt,bbding}
\RequirePackage[many]{tcolorbox}

\tcbset{
	common/.style={
		fontupper=\fzfs,
		sharp corners,
		lower separated=false,
		% before upper={\setlength{\parindent}{\normalparindent}},
		coltitle=black,
		colback=white,
		colframe=gray!25,
		fonttitle=\bfseries,
		enhanced,
		breakable,
		attach boxed title to top left={
		  yshift=0mm,},
		boxed title style={
			sharp corners,
			colframe=gray!25,
			colback=gray!25,
		},
		separator sign={.},
	},
	claim/.style={
		coltitle=black,
		colback=gray!10,
		colframe=gray!50,
		fonttitle=\bfseries,
		detach title,
		boxrule=0pt,
		leftrule=2pt,
		attach title to upper,
		sharp corners,
		left=1mm,
	}
,}

\newtcolorbox[auto counter, number within=section]{thmcounter}{}

\DeclareTColorBox[use counter from=thmcounter]{definition}{ o t\label g }{
	common,
	IfValueTF={#1}{title={定义 \thetcbcounter【#1】}}{title=定义 \thetcbcounter},
	IfBooleanTF={#2}{label=#3}{}}

\DeclareTColorBox[use counter from=thmcounter]{theorem}{ o t\label g }{
	common,
	IfValueTF={#1}{title={定理 \thetcbcounter【#1】}}{title=定理 \thetcbcounter},
	IfBooleanTF={#2}{label=#3}{}}

\DeclareTColorBox[use counter from=thmcounter]{lemma}{ o t\label g }{
	common,
	IfValueTF={#1}{title={引理 \thetcbcounter【#1】}}{title=引理 \thetcbcounter},
	IfBooleanTF={#2}{label=#3}{}}

\DeclareTColorBox[use counter from=thmcounter]{corollary}{ o t\label g }{
	common,
	IfValueTF={#1}{title={推论 \thetcbcounter【#1】}}{title=推论 \thetcbcounter},
	IfBooleanTF={#2}{label=#3}{}}

\DeclareTColorBox[use counter from=thmcounter]{postulate}{ o t\label g }{
	common,
	IfValueTF={#1}{title={公设 \thetcbcounter【#1】}}{title=公设 \thetcbcounter},
	IfBooleanTF={#2}{label=#3}{}}

\DeclareTColorBox[use counter from=thmcounter]{axiom}{ o t\label g }{
	common,
	IfValueTF={#1}{title={公理 \thetcbcounter【#1】}}{title=公理 \thetcbcounter},
	IfBooleanTF={#2}{label=#3}{}}

\DeclareTColorBox[use counter from=thmcounter]{example}{ o t\label g }{
	common,
	IfValueTF={#1}{title={例 \thetcbcounter【#1】}}{title=例 \thetcbcounter},
	IfBooleanTF={#2}{label=#3}{}}

\DeclareTColorBox[use counter from=thmcounter]{problem}{ o t\label g }{
	common,
	IfValueTF={#1}{title={问题【#1】}}{title=问题},
	IfBooleanTF={#2}{label=#3}{}}
  
\DeclareTColorBox[use counter from=thmcounter]{proposition}{ o t\label g }{
	common,
	IfValueTF={#1}{title={命题 \thetcbcounter【#1】}}{title=命题 \thetcbcounter},
	IfBooleanTF={#2}{label=#3}{}}


  
\DeclareTColorBox[no counter]{note}{ o t\label g }{
	claim,
	IfValueTF={#1}{title={笔记【#1】$\quad$}}{title=笔记$\quad$},
	IfBooleanTF={#2}{label=#3}{}}

\RequirePackage{amsthm}
\let\proof\relax
\let\endproof\relax


\newenvironment{proof}{
  \par\noindent\textbf{证明\quad}}{
   \hfill$\Box$\quad
  \par}

\newtheoremstyle{thmstyle}{3pt}{3pt}{\fzfs}{-3pt}{
	\bfseries}{}{0.5em}{\thmname{#1} \thmnumber{#2} \thmnote{【 #3 】}}
\newtheoremstyle{solvestyle}{3pt}{3pt}{\fzsong}{-3pt}{
	\bfseries}{}{0.5em}{\thmname{#1} \thmnote{【 #3 】}}

%\theoremstyle{thmstyle} %theorem style
%\newtheorem{theorem}{定理}[section]
%%\newtheorem{definition}[theorem]{定义}
%\newtheorem{lemma}[theorem]{引理}
%\newtheorem{corollary}[theorem]{推论}
%\newtheorem{postulate}[theorem]{公设}
%\newtheorem{axiom}[theorem]{公理}
%\newtheorem{example}[theorem]{例}
%\newtheorem{problem}[theorem]{问题}
%\newtheorem{proposition}[theorem]{命题}

\theoremstyle{solvestyle}
\newtheorem{solution}{解}

