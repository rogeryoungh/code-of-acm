import{_ as s,c as i,o as a,a2 as n}from"./chunks/framework.Bx6qu0xe.js";const F=JSON.parse('{"title":"并查集","description":"","frontmatter":{},"headers":[],"relativePath":"template/dsu.md","filePath":"template/dsu.md"}'),h={name:"template/dsu.md"},t=n(`<h1 id="并查集" tabindex="-1">并查集 <a class="header-anchor" href="#并查集" aria-label="Permalink to &quot;并查集&quot;">​</a></h1><div class="language-cpp vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">cpp</span><pre class="shiki shiki-themes github-light github-dark vp-code"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">struct</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> DSU</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> {</span></span>
<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">	std</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">::vector</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&lt;int&gt;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> fa;</span></span>
<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">	DSU</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">int</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> n</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) : </span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">fa</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(n) {</span></span>
<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">		std</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">::</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">iota</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(fa.</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">begin</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(), fa.</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">end</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(), </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">0</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">);</span></span>
<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">	}</span></span>
<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">	int</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> find</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">int</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> x</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>
<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">		return</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> fa[x] </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">==</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> x </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">?</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> x </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">:</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> fa[x] </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> find</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(fa[x]);</span></span>
<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">	}</span></span>
<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">	bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> same</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">int</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> x</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">int</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> y</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>
<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">		return</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> find</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(x) </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">==</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> find</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(y);</span></span>
<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">	}</span></span>
<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">	void</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> merge</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">int</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> x</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">int</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> y</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>
<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">		fa[</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">find</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(x)] </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> find</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(y);</span></span>
<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">	}</span></span>
<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">};</span></span></code></pre></div><h2 id="测试例题" tabindex="-1">测试例题 <a class="header-anchor" href="#测试例题" aria-label="Permalink to &quot;测试例题&quot;">​</a></h2><ul><li><a href="https://judge.yosupo.jp/problem/unionfind" target="_blank" rel="noreferrer">yosupo Unionfind</a></li></ul>`,4),k=[t];function l(p,e,E,r,d,g){return a(),i("div",null,k)}const o=s(h,[["render",l]]);export{F as __pageData,o as default};
