import { DefaultTheme, defineConfig } from 'vitepress'

// https://vitepress.dev/reference/site-config
export default defineConfig({
  title: "算法笔记",
  description: "rogeryoungh 的算法笔记",

  cleanUrls: true,
  markdown: {
    math: true,
  },

  themeConfig: {
    // https://vitepress.dev/reference/default-theme-config
    nav: [
      { text: '主页', link: '/' },
      { text: '模板', link: '/template/base' }
    ],

    sidebar: sidebarItems(),

    socialLinks: [
      { icon: 'github', link: 'https://github.com/vuejs/vitepress' }
    ]
  }
})

function sidebarItems(): DefaultTheme.Sidebar {
  return {
    '/template/': [
      {
        text: '基础',
        items: [
          { text: '介绍', link: '/template/' },
          { text: '初始文件', link: '/template/base' },
          { text: '二维数组', link: '/template/vec2d' },
          { text: '快速幂', link: '/template/qpow' },
          { text: '二分查找', link: '/template/binary-search' },
          { text: 'modint', link: '/template/modint' },
        ]
      },
      {
        text: '数据结构',
        items: [
          { text: '并查集', link: '/template/dsu' },
          { text: 'Sparse Table', link: '/template/sparse-table' },
          { text: '树状数组', link: '/template/fwtree' },
        ]
      },
      {
        text: '数学',
        items: [
          { text: '矩阵', link: '/template/matrix' },
          { text: 'Gauss 消元', link: '/template/gauss' },
          { text: 'EXGCD', link: '/template/exgcd' },
          { text: '筛法', link: '/template/sieve' },
          { text: '素性测试', link: '/template/primality-test' },
          { text: '质因分解', link: '/template/factor' },
          { text: '中国剩余定理', link: '/template/crt' },
          { text: 'Floor Sum', link: '/template/floor-sum' },
          { text: '二次剩余', link: '/template/quad-residue' },
        ]
      },
      {
        text: '字符串',
        items: [
          { text: 'KMP', link: '/template/kmp' },
          { text: 'Z Algorithm', link: '/template/z-algo' },
        ]
      },
      {
        text: '无用',
        items: [
          { text: '小技巧', link: '/template/some-trick' },
          { text: '快读', link: '/template/fastio' },
        ]
      },
    ]
  }
}
