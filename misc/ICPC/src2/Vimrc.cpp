source $VIMRUNTIME/defaults.vim
set tabstop=4
set nocompatible
set shiftwidth=4
set autoindent
"set smartindent
set cindent
set ruler
set showcmd
set incsearch
set number
set relativenumber
set cino+=L0 "Doesn't untab when typing colons
syntax on
filetype indent on

inoremap {<CR>  {<CR>}<Esc>O
inoremap {}     {}
imap jk         <Esc>
set belloff=all
