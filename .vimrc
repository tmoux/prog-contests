source $VIMRUNTIME/defaults.vim
set tabstop=4
set nocompatible
set shiftwidth=4
set expandtab
set autoindent
set ruler
set showcmd
set incsearch
set directory^=~/.vim/tmp//
set shellslash
set smartindent
set visualbell
set t_vb=
set number
filetype indent on
inoremap {<CR>  {<CR>}<Esc>O
inoremap {}     {}
imap jk         <Esc>
map <C-a> <esc>ggVG<CR>

nnoremap <expr> j v:count ? (v:count > 5 ? "m'" . v:count : '') . 'j' : 'gj'
nnoremap <expr> k v:count ? (v:count > 5 ? "m'" . v:count : '') . 'k' : 'gk'
command Codef :.-1read ~/.vim/snippets/codeforces.cpp

"Correct highlighting in visual mode
highlight Visual cterm=reverse ctermbg=NONE

"Latex stuff
let g:livepreview_previewer = 'zathura'
set updatetime=1000
let g:tex_no_error=1
map LLPStartPreview LL
"autocomplete begin/end environments with \bb
inoremap \bb <Esc>bcw\begin{<C-R>"}<CR>\end{<C-R>"}<Esc>O
"autocomplete \[ like { in c/c++
inoremap \[<CR>  \[<CR>\]<Esc>O
inoremap \[\]     \[\]

"wyvern syntax highlighting
autocmd BufNewFile,BufRead *.wyv,*.wyt set syntax=wyvern
