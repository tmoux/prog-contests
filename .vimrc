source $VIMRUNTIME/defaults.vim
set tabstop=4
set nocompatible
set shiftwidth=4
set expandtab
set autoindent
set smartindent
set ruler
set showcmd
set incsearch
set directory^=~/.vim/tmp//
set shellslash
filetype indent on
let g:tex_flavor='latex'
autocmd Filetype tex setl updatetime=1
let g:livepreview_previewer = 'open zathura'
inoremap {<CR>  {<CR>}<Esc>O
inoremap {}     {}
imap jk         <Esc>
map <C-a> <esc>ggVG<CR>
command Codef :.-1read ~/.vim/snippets/codeforces.cpp
command Usaco :.-1read ~/.vim/snippets/usaco.cpp
