#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
using ll = long long;

const int maxn = 1e6+6;
int n, m;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < (m)/2; i++) {
        for (int j = 0; j < n; j++) {
            cout << (j+1) << ' ' << (i+1) << '\n';
            cout << (n-j) << ' ' << (m-i) << '\n';
        }
    }
    if (m&1) {
        for (int j = 0; j < n/2; j++) {
            cout << (j+1) << ' ' << (m/2+1) << '\n';
            cout << (n-j) << ' ' << (m/2+1) << '\n';
        }
        if (n&1) {
            cout << (n/2+1) << ' ' << (m/2+1) << '\n';
        }
    }
}



times in msec
 clock   self+sourced   self:  sourced script
 clock   elapsed:              other lines

000.003  000.003: --- VIM STARTING ---
000.083  000.080: Allocated generic buffers
000.107  000.024: locale set
000.116  000.009: GUI prepared
000.117  000.001: clipboard setup
000.120  000.003: window checked
000.478  000.358: inits 1
000.497  000.019: parsing arguments
000.497  000.000: expanding arguments
000.522  000.025: shell init
1001.036  1000.514: xsmp init
1001.609  000.573: Termcap init
1001.708  000.099: inits 2
1002.071  000.363: init highlight
1002.943  000.617  000.617: sourcing /usr/share/vim/vim80/debian.vim
1005.529  002.168  002.168: sourcing /usr/share/vim/vim80/syntax/syncolor.vim
1005.826  002.614  000.446: sourcing /usr/share/vim/vim80/syntax/synload.vim
1011.739  005.785  005.785: sourcing /usr/share/vim/vim80/filetype.vim
1011.776  008.710  000.311: sourcing /usr/share/vim/vim80/syntax/syntax.vim
1011.799  009.608  000.281: sourcing $VIM/vimrc
1012.275  000.270  000.270: sourcing /usr/share/vim/vim80/syntax/nosyntax.vim
1012.556  000.172  000.172: sourcing /usr/share/vim/vim80/syntax/syncolor.vim
1012.659  000.340  000.168: sourcing /usr/share/vim/vim80/syntax/synload.vim
1012.687  000.718  000.108: sourcing /usr/share/vim/vim80/syntax/syntax.vim
1012.743  000.011  000.011: sourcing /usr/share/vim/vim80/filetype.vim
1012.820  000.036  000.036: sourcing /usr/share/vim/vim80/ftplugin.vim
1012.893  000.031  000.031: sourcing /usr/share/vim/vim80/indent.vim
1012.997  001.149  000.353: sourcing /usr/share/vim/vim80/defaults.vim
1013.188  000.013  000.013: sourcing /usr/share/vim/vim80/filetype.vim
1013.238  000.009  000.009: sourcing /usr/share/vim/vim80/indent.vim
1014.845  001.542  001.542: sourcing /home/tmou/.vim/autoload/plug.vim
1015.673  000.325  000.325: sourcing /usr/share/vim/vim80/ftoff.vim
1021.228  000.018  000.018: sourcing /home/tmou/.vim/plugged/vim-markdown/ftdetect/markdown.vim
1021.312  004.838  004.820: sourcing /usr/share/vim/vim80/filetype.vim
1021.371  000.010  000.010: sourcing /usr/share/vim/vim80/ftplugin.vim
1021.422  000.008  000.008: sourcing /usr/share/vim/vim80/indent.vim
1021.469  009.644  001.750: sourcing $HOME/.vimrc
1021.472  000.149: sourcing vimrc file(s)
1022.024  000.462  000.462: sourcing /home/tmou/.vim/plugin/surround.vim
1022.673  000.584  000.584: sourcing /home/tmou/.vim/plugged/bullets.vim/plugin/bullets.vim
1022.980  000.061  000.061: sourcing /usr/share/vim/vim80/plugin/getscriptPlugin.vim
1023.182  000.184  000.184: sourcing /usr/share/vim/vim80/plugin/gzip.vim
1023.398  000.201  000.201: sourcing /usr/share/vim/vim80/plugin/logiPat.vim
1023.440  000.025  000.025: sourcing /usr/share/vim/vim80/plugin/manpager.vim
1023.642  000.189  000.189: sourcing /usr/share/vim/vim80/plugin/matchparen.vim
1024.184  000.526  000.526: sourcing /usr/share/vim/vim80/plugin/netrwPlugin.vim
1024.252  000.041  000.041: sourcing /usr/share/vim/vim80/plugin/rrhelper.vim
1024.298  000.026  000.026: sourcing /usr/share/vim/vim80/plugin/spellfile.vim
1024.469  000.153  000.153: sourcing /usr/share/vim/vim80/plugin/tarPlugin.vim
1024.568  000.075  000.075: sourcing /usr/share/vim/vim80/plugin/tohtml.vim
1024.764  000.177  000.177: sourcing /usr/share/vim/vim80/plugin/vimballPlugin.vim
1024.969  000.176  000.176: sourcing /usr/share/vim/vim80/plugin/zipPlugin.vim
1024.973  000.621: loading plugins
1025.019  000.046: loading packages
1025.044  000.025: loading after plugins
1025.058  000.014: inits 3
1025.334  000.276: reading viminfo
1027.357  002.023: setup clipboard
1027.371  000.014: setting raw mode
1027.375  000.004: start termcap
1027.381  000.006: clearing screen
1027.621  000.240: opening buffers
1027.725  000.104: BufEnter autocommands
1027.727  000.002: editing files in windows
1027.848  000.121: VimEnter autocommands
1027.849  000.001: before starting main loop
1028.028  000.179: first screen update
1028.029  000.001: --- VIM STARTED ---


times in msec
 clock   self+sourced   self:  sourced script
 clock   elapsed:              other lines

000.003  000.003: --- VIM STARTING ---
000.081  000.078: Allocated generic buffers
000.103  000.022: locale set
000.112  000.009: GUI prepared
000.116  000.004: clipboard setup
000.119  000.003: window checked
000.487  000.368: inits 1
000.507  000.020: parsing arguments
000.508  000.001: expanding arguments
000.529  000.021: shell init
1001.005  1000.476: xsmp init
1001.486  000.481: Termcap init
1001.578  000.092: inits 2
1001.911  000.333: init highlight
1002.705  000.577  000.577: sourcing /usr/share/vim/vim80/debian.vim
1004.037  000.965  000.965: sourcing /usr/share/vim/vim80/syntax/syncolor.vim
1004.148  001.201  000.236: sourcing /usr/share/vim/vim80/syntax/synload.vim
1009.765  005.573  005.573: sourcing /usr/share/vim/vim80/filetype.vim
1009.799  006.982  000.208: sourcing /usr/share/vim/vim80/syntax/syntax.vim
1009.820  007.813  000.254: sourcing $VIM/vimrc
1010.256  000.244  000.244: sourcing /usr/share/vim/vim80/syntax/nosyntax.vim
1010.517  000.161  000.161: sourcing /usr/share/vim/vim80/syntax/syncolor.vim
1010.612  000.316  000.155: sourcing /usr/share/vim/vim80/syntax/synload.vim
1010.638  000.659  000.099: sourcing /usr/share/vim/vim80/syntax/syntax.vim
1010.690  000.011  000.011: sourcing /usr/share/vim/vim80/filetype.vim
1010.761  000.033  000.033: sourcing /usr/share/vim/vim80/ftplugin.vim
1010.830  000.029  000.029: sourcing /usr/share/vim/vim80/indent.vim
1010.926  001.059  000.327: sourcing /usr/share/vim/vim80/defaults.vim
1011.091  000.012  000.012: sourcing /usr/share/vim/vim80/filetype.vim
1011.138  000.009  000.009: sourcing /usr/share/vim/vim80/indent.vim
1012.617  001.420  001.420: sourcing /home/tmou/.vim/autoload/plug.vim
1013.380  000.301  000.301: sourcing /usr/share/vim/vim80/ftoff.vim
1018.500  000.016  000.016: sourcing /home/tmou/.vim/plugged/vim-markdown/ftdetect/markdown.vim
1018.576  004.457  004.441: sourcing /usr/share/vim/vim80/filetype.vim
1018.629  000.010  000.010: sourcing /usr/share/vim/vim80/ftplugin.vim
1018.675  000.008  000.008: sourcing /usr/share/vim/vim80/indent.vim
1018.718  008.874  001.598: sourcing $HOME/.vimrc
1018.720  000.122: sourcing vimrc file(s)
1019.206  000.406  000.406: sourcing /home/tmou/.vim/plugin/surround.vim
1019.818  000.552  000.552: sourcing /home/tmou/.vim/plugged/bullets.vim/plugin/bullets.vim
1020.103  000.057  000.057: sourcing /usr/share/vim/vim80/plugin/getscriptPlugin.vim
1020.294  000.175  000.175: sourcing /usr/share/vim/vim80/plugin/gzip.vim
1020.496  000.188  000.188: sourcing /usr/share/vim/vim80/plugin/logiPat.vim
1020.537  000.024  000.024: sourcing /usr/share/vim/vim80/plugin/manpager.vim
1020.728  000.179  000.179: sourcing /usr/share/vim/vim80/plugin/matchparen.vim
1021.243  000.500  000.500: sourcing /usr/share/vim/vim80/plugin/netrwPlugin.vim
1021.304  000.037  000.037: sourcing /usr/share/vim/vim80/plugin/rrhelper.vim
1021.346  000.024  000.024: sourcing /usr/share/vim/vim80/plugin/spellfile.vim
1021.503  000.140  000.140: sourcing /usr/share/vim/vim80/plugin/tarPlugin.vim
1021.592  000.067  000.067: sourcing /usr/share/vim/vim80/plugin/tohtml.vim
1021.768  000.159  000.159: sourcing /usr/share/vim/vim80/plugin/vimballPlugin.vim
1021.948  000.153  000.153: sourcing /usr/share/vim/vim80/plugin/zipPlugin.vim
1021.952  000.571: loading plugins
1021.993  000.041: loading packages
1022.017  000.024: loading after plugins
1022.033  000.016: inits 3
1022.294  000.261: reading viminfo
1024.291  001.997: setup clipboard
1024.304  000.013: setting raw mode
1024.308  000.004: start termcap
1024.313  000.005: clearing screen
1024.544  000.231: opening buffers
1024.641  000.097: BufEnter autocommands
1024.643  000.002: editing files in windows
1024.757  000.114: VimEnter autocommands
1024.758  000.001: before starting main loop
1024.926  000.168: first screen update
1024.927  000.001: --- VIM STARTED ---
