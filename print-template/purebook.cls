\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{purebook}[2023/03/10 v0.0.2 Pure Document Class]

\LoadClass[a4paper,oneside,UTF8,fontset=none]{ctexbook}

%%%%  purebook 设置  %%%%

%% 数学环境

\RequirePackage{amsmath, amsfonts, amssymb}
\RequirePackage{mathtools, mathrsfs}
\RequirePackage[xindy]{imakeidx}

%% 页面设置

\RequirePackage{geometry}
\geometry{
  paper=a4paper,
  top=25.4mm,
  bottom=25.4mm,
  left=20mm,
  right=20mm,
  headheight=21.7mm,
  headsep=4mm,
  footskip=12mm,
}
\pagestyle{plain}

%% 颜色

\RequirePackage[table]{xcolor}

\definecolor{linkcolor}{RGB}{128,0,0}
\definecolor{frenchplum}{RGB}{190,20,83}

%% 链接

\RequirePackage{hyperref}
\hypersetup{
  breaklinks=true,
  unicode=true,
  linktoc=all,
  bookmarksnumbered=true,
  bookmarksopen=true,
  colorlinks=true,
  linkcolor=linkcolor,
  citecolor=linkcolor,
  urlcolor=linkcolor,
}

%% 目录

\ctexset{
  section/titleformat = \raggedright
}
\setcounter{secnumdepth}{3}
\setcounter{tocdepth}{3}
%% 字体

\setCJKmainfont[BoldFont={Noto Serif CJK SC Bold},ItalicFont={Noto Sans CJK SC}]{Noto Serif CJK SC}
\setCJKsansfont{Noto Sans CJK SC}
\setCJKmonofont{LXGW WenKai}
\setCJKfamilyfont{zhsong}{Noto Serif CJK SC}
\setCJKfamilyfont{zhhei}{Noto Sans CJK SC}
\setCJKfamilyfont{zhkai}{LXGW WenKai}
\setCJKfamilyfont{zhbsong}{Noto Serif CJK SC Bold}
\newcommand*{\zhsong}{\CJKfamily{zhsong}}
\newcommand*{\zhhei}{\CJKfamily{zhhei}}
\newcommand*{\zhkai}{\CJKfamily{zhkai}}
\newcommand*{\zhbsong}{\CJKfamily{zhbsong}}

%% 代码

\RequirePackage{listings}
\setmonofont{JetBrains Mono}

\definecolor{codecolorkeywords}{RGB}{0,96,255}
\definecolor{codecolorcomments}{RGB}{127,127,127}
\definecolor{codecolorxmlcomments}{rgb}{0.5,0.5,0.5}
\definecolor{codecolorstrings}{RGB}{127,127,127}
\definecolor{codecolortypes}{rgb}{0.17,0.57,0.68}
\definecolor{codecolorbg}{RGB}{244,247,248}

\lstset{
  basicstyle=\ttfamily\small \lst@ifdisplaystyle\fi,
  % Code
  columns=fullflexible,
  tabsize=2,
  showspaces=false,
  showstringspaces=false,
  showtabs=false,
  numbers=left,
  numbersep=10pt,
  xleftmargin=2em,
  stepnumber=1,
  firstnumber=1,
  numberfirstline=true,
  numberstyle=\ttfamily\small\color{gray},
  % Code design
  emph={ll},
  keywordstyle=\bfseries,
  commentstyle=\color{codecolorcomments},
  stringstyle=\color{codecolorstrings},
  emphstyle=\bfseries,
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
  morekeywords={return},
  %other
  literate=
    {==}{{==}}2
    {->}{{->}}2
    {!=}{{!=}}2
    {>=}{{>=}}2
    {<=}{{<=}}2
    {<>}{{<>}}2
    {>>}{{>>}}2
    {<<}{{<<}}2
    {\&\&}{{\&\&}}2,
}

\RequirePackage{caption}

\DeclareCaptionFormat{codecaptionformat}{%
  \parbox{\linewidth}{#1#2 \ttfamily#3}
}

\captionsetup[lstlisting]{format=codecaptionformat}
\renewcommand{\lstlistingname}{
  {\ttfamily </> 代码}
}
%% 定理环境

\RequirePackage{amsthm}
\let\proof\relax
\let\endproof\relax

\newenvironment{proof}
  {\par\noindent\textbf{证明\quad}\zhkai}
  {\hfill$\Box$\quad\par}

\newtheoremstyle{thmstyle}
  {3pt}{3pt}{\zhkai}{-3pt}{\bfseries}{}{0.5em}
  {\thmname{#1} \thmnumber{#2} \thmnote{「{#3}」}}
\newtheoremstyle{solvestyle}
  {3pt}{3pt}{\zhkai}{-3pt}{\bfseries}{}{0.5em}
  {\thmname{#1} \thmnote{「{#3}」}}

\RequirePackage{pifont,manfnt,bbding}
\RequirePackage[many]{tcolorbox}

\theoremstyle{thmstyle} %theorem style
\newtheorem{theorem}{定理}[section]
\newtheorem{definition}[theorem]{定义}
\newtheorem{lemma}[theorem]{引理}
\newtheorem{corollary}[theorem]{推论}
\newtheorem{postulate}[theorem]{公设}
\newtheorem{axiom}[theorem]{公理}
\newtheorem{example}[theorem]{例}
\newtheorem{problem}[theorem]{问题}
\newtheorem{proposition}[theorem]{命题}

\theoremstyle{solvestyle}
\newtheorem{solution}{解}

