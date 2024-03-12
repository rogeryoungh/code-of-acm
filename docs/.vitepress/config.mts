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
          { text: '初始文件', link: '/template/base' },
          { text: '二维数组', link: '/template/vec2d' },
          { text: '快速幂', link: '/template/qpow' },
          { text: '二分查找', link: '/template/binary-search' },
        ]
      },
      {
        text: '数据结构',
        items: [
          { text: '并查集', link: '/template/dsu' },
        ]
      },
    ]
  }
}
