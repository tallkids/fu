
      ＵｎｉｘＷＳ用ファイル管理ユーティリティ  【  ｆｕ  Ver3.07  】

                                         Copyright (C) 1990-1998 T.Tashiro

１．概要
    ｆｕはＵｎｉｘＷＳ上でファイルの削除、コピー、ディレクトリツリーの表示等
  を簡単に行うためのツールです。この他に、エディタの起動、シェルの実行（ヒス
  トリー機能付き）ができるなど、ｆｕをシェルのかわりに使用する事もできます。
  また、コマンド実行のためのキーアサイン変更や、コマンドの追加登録なども
  簡単にでき、ユーザの好みでカスタマイズする事ができます。

２．ｆｕのコンパイル及びインストール
  ２．１ コンパイル
     makeを実行します。この際のオプションで対応機種を設定します。

        make hpux         HP-UX on HP9000 series
        make linux        Linux
        make bsdi         BSDI
        make h2050        HI-UX on HITACHI 2050 series
        make i386bsd      386BSD
        make panix        PANIX
        make minix        Minix
        make sunos        SunOS
        make news3400     NEWS3400

       いずれの場合もxfuを作成する場合は機種名のオプションに'-x'を付けて下さい。
       例:  make hpux-x

       注意: 手元に機械がないため hpux と linux, bsdi 以外は試してません。
             (だれかパッチを作って下さい。)

       カレントディレクトリに'fu'(Xバージョンでは'xfu')が作成されます。

　２．２ インストール
    'fu'('xfu')をコマンド検索パスの通っている、ディレクトリにコピーする。
        （'/usr/local/bin'等に格納する事を、お勧めします）

３．ｆｕの起動方法
 ３．１ ノーマルバージョン('fu')
  フォーマット:
    $ fu [options]

  オプション:
    -a                       ASCIIコードのみの表示モードにする。
                             漢字があった場合には'?'で置換して表示する。
    -k                       漢字コードも使用可能とする。(デフォルト)
    -s                       漢字コードにShift-JISを使用する。
                             (H2050,HP9000ではデフォルト)
    -e                       漢字コードにEUCを使用する。
                             (SunSPARC,MINIX等ではデフォルト)

 ３．２ X対応バージョン('xfu')
  フォーマット:
    $ xfu [options]

  オプション:
    -a                       ASCIIコードのみの表示モードにする。
                             漢字があった場合には'?'で置換して表示する。
    -k                       漢字コードも使用可能とする。(デフォルト)
    -s                       漢字コードにShift-JISを使用する。
                             (H2050,HP9000ではデフォルト)
    -e                       漢字コードにEUCを使用する。
    -display host:display    X Windowサーバホスト名
    -geometry geom           xfuのウインドウジオメトリ
    -name title              ウインドウタイトル名
    -fg color                フォアグランドカラー
    -bg color                バックグランドカラー
    -fn fontname             ASCII文字フォント名
    -fr font_kana            仮名文字フォント名
    -fk font_kanji           漢字文字フォント名

  リソース:
    xfu.Title:               ウインドウタイトル名(例:'Xfu')
    xfu.Geometry:            ウインドウジオメトリ(例:'21x40+20+20')
    xfu.Foreground:          フォアグランドカラー(例:'White')
    xfu.Background:          バックグランドカラー(例:'Black')
    xfu.Font:                ASCII文字フォント名(例:'asc08')
    xfu.KanaFont:            仮名文字フォント名(例:'j7kana08')
    xfu.KanjiFont:           漢字文字フォント名(例:'sjis16')

４．ｆｕの表示画面
  ｆｕにはファイル表示画面と、ディレクトリ表示画面があります。それらを以下に
  示します。
  ４．１ ファイル表示画面
--------------------------------------------------------------------------------
Current Dir(0) : /usr/tashiro
 [.             ]drwxr-xr-x 11/08 18:01  .profile       -rw-r--r-- 11/05 10:01^^
 [..            ]drwxr-xr-x 11/08 11:10  .rhosts        -rw-r--r-- 10/30 09:01
 [DDC           ]drwxrwxrwx 11/01 19:24  .setup.fu      -rw-r--r-- 07/29 16:49
 [JUS_FREE      ]drwxr-xr-x 10/15 16:22  .setup.mfu     -rw-r--r-- 10/29 11:05PP
 [Wnn           ]drwxrwxrwx 10/25 1990   .wsdb.def      -rw-r--r-- 10/29 15:49RR
 [bin           ]drwxr-xr-x 11/08 11:10  .tree.fu       -rw-r--r-- 11/05 09:59EE
 [bitmaps       ]drwxr-xr-x 10/28 13:00  .xinitrc       -rw-r--r-- 10/09 08:11VV
 [comm          ]drwxr-xr-x 10/30 16:06  .xsession      -rw-r--r-- 10/09 08:50
 [projectA      ]drwxr-xr-x 09/27 15:18  calendar       -rw-r--r-- 11/07 09:55
 [image         ]drwxr-xr-x 08/01 21:58  emacs.rc       -rw-r--r-- 05/20 08:25--
 [nfs           ]drwxr-xr-x 12/26 1990   jldx00         -rw-rw-rw- 09/27 17:22
 [rex           ]drwxr-xr-x 10/07 20:59  jldx10         -rw-rw-rw- 09/27 17:24
 [rexapp        ]drwxr-xr-x 10/29 10:58  kankan         -rw-rw-rw- 10/24 09:10NN
 [test          ]drwxr-xr-x 10/15 07:55                                       EE
 [tool          ]drwxr-xr-x 11/07 13:19                                       XX
 [txt           ]drwxr-xr-x 10/29 10:52                                       TT
  .Xresources    -rw-r--r-- 11/05 10:18
  .dbacc.def     -rw-r--r-- 10/28 13:51
  .mwmrc         -rw-r--r-- 10/30 08:43                                       vv
== File Management Utility Ver.3.05 =============================== T.Tashiro ==
Command : Copy Delete Edit Find Quit Shell Tree eXecute Mount UnMount (1) (2)
          (4)
Find : *
--------------------------------------------------------------------------------

      (1) 1行     絶対ディレクトリパスが表示されます。
                  括弧内の数値はその時点でスタックに積まれているパスの数を表す。
      (2) 2-20行  ファイル名の表示領域(79-80カラムはスクロールバー)
        ・1列表示モードの場合
   * calendar       -rw-r--r--   1 tashiro  group        1384 Apr  8 10:16 1991
            カラム      意  味
            1      : '*'で選択状態にある事を示す。
            2,17   : '[',']'でそのファイルがディレクトリである事を示す。
            3-16   : ファイル名
            18     : 'd'は、ディレクトリであることを示す。
                     'c'は、キャラクタデバイスであることを示す。
                     'b'は、ブロックデバイスであることを示す。
                     'p'は、FIFOデバイスであることを示す。
                     's'は、ソケットデバイスであることを示す。
            19-21  : 'r','w','x'は、それぞれオーナーの読み込み、書き込み、実行
                     許可を示す。実行許可が's'の場合set uidビットが立っている.
            22-24  : 'r','w','x'は、それぞれグループの読み込み、書き込み、実行
                     許可を示す。実行許可が's'の場合set gidビットが立っている.
            25-27  : 'r','w','x'は、それぞれ他ユーザの読み込み、書き込み、実行
                     許可を示す。実行許可が't'の場合stickyビットが立っている.
            29-31  : ファイルのリンク数
            33-40  : ファイルのオーナー名
            42-49  : ファイルのオーナーグループ名
            51-58  : ファイルサイズ(Byte単位)
            60-65  : ファイルが最後に変更された月／日
            67-71  : ファイルが最後に変更された時：分
            73-76  : ファイルが最後に変更された年
        ・2列表示モードの場合
          * calendar       drwxrw-r-x 04/17 17:17
            カラム      意  味
            1      : '*'で選択状態にある事を示す。
            2,17   : '[',']'でそのファイルがディレクトリである事を示す。
            3-16   : ファイル名
            18     : 'd'は、ディレクトリであることを示す。
                     'c'は、キャラクタデバイスであることを示す。
                     'b'は、ブロックデバイスであることを示す。
                     'p'は、FIFOデバイスであることを示す。
                     's'は、ソケットデバイスであることを示す。
            19-21  : 'r','w','x'は、それぞれオーナーの読み込み、書き込み、実行
                     許可を示す。実行許可が's'の場合set uidビットが立っている.
            22-24  : 'r','w','x'は、それぞれグループの読み込み、書き込み、実行
                     許可を示す。実行許可が's'の場合set gidビットが立っている.
            25-27  : 'r','w','x'は、それぞれ他ユーザの読み込み、書き込み、実行
                     許可を示す。実行許可が't'の場合stickeyビットが立っている.
            29-33  : ファイルが最後に変更された月／日
            35-39  : ファイルが最後に変更された時：分(変更されてから半年以上
	             経っている場合変更した年が表示される)
        ・4列表示モードの場合
          * calendar
            カラム      意  味
            1      : '*'で選択状態にある事を示す。
            2,17   : '[',']'でそのファイルがディレクトリである事を示す。
            3-16   : ファイル名
      (3) 21行    インフォメーションライン ｆｕの正式名称とバージョン
      (4) 22-23行 コマンドメニュー         使用できる主なコマンド
      (5) 24行    ファイル名検索マスク

   (注)・X-Windowのxterm等で行数を変更している場合はそれに合わせて表示も調整
         されます。(ダイナミックには変更されません)
       ・'xfu'ではウインドウを変形させることにより行数／列数がダイナミックに
         変更されます。

  ４．２ ディレクトリ表示画面
--------------------------------------------------------------------------------
Path : /hd/tashiro/GAEA
 /              >                                                             ^^
 +- hd             >
     +- tashiro
         +- DDC            >
         +- GAEA           >                                                  PP
         +- JUS_FREE       >                                                  RR
         +- Wnn            >                                                  EE
         +- bin                                                               VV
         |   +- mo_eps         >
         +- bitmaps        >
         +- compkg         >
         |   +- vos3           >                                              --
         |       +- single_chk
         +- gtproject      >
         +- image          >                                                  NN
         +- nfs            >                                                  EE
         +- rex            >                                                  XX
         +- rexapp         >                                                  TT
         +- test           >
         +- tool           >
         +- txt            >
                                                                              vv
--------------------------------------------------------------------------------
      (1) 1行     カーソルが指しているディレクトリの絶対パス
      (2) 2-23行  ディレクトリツリー表示領域(79-80カラムはスクロールバー)
                  '>'が後ろについているディレクトリは、未検索ディレクトリを示す

５．ｆｕのキー操作と機能
    使用しているWSが2050でH-Windowの場合または、'xfu'の場合にはマウスを使用す
  ることができます。マウスの使用方法については実際にオペレーションを行ない自分
  で考えて下さい。
    (注)ここに示しているのは2050のデフォルトの設定です。
  ５．１ ファイル表示画面でのキー操作と機能
      矢印キー      ：  ファイル選択用カーソルの移動
      SHIFT + 上    ：  １頁前のファイル表示画面に移動
      SHIFT + 下    ：  １頁後のファイル表示画面に移動
      前頁キー      ：  １頁前のファイル表示画面に移動
      次頁キー      ：  １頁後のファイル表示画面に移動
      スペースキー  ：  カーソル位置にあるファイルの選択状態の切り替え
      リターンキー  ：  ディレクトリファイルの場合
                            →ディレクトリの移動
                        アーカイブファイルの場合
                            →アーカイブされているファイル名一覧を表示
                        その他のファイルの場合
                            →ファイル内容の表示（ｍｏｒｅ表示）
      削除キー      ：  ファイル/ディレクトリの削除
      Homeキー      ：  カレントディレクトリの全てのファイルを選択/選択解除
      Ctrl-B        ：  カーソルを左に移動
      Ctrl-F        ：  カーソルを右に移動
      Ctrl-N        ：  カーソルを下に移動
      Ctrl-P        ：  カーソルを上に移動
      Ctrl-Z        ：  １頁前のファイル表示画面に移動
      Ctrl-V        ：  １頁後のファイル表示画面に移動
      Ctrl-L        ：  画面の再描画
      Ctrl-X Ctrl-C ：  ｆｕの終了
      "+"           ：  カレントディレクトリをスタックに積む
      "-"           ：  スタックに積まれたディレクトリをカレントにする
      "/"           ：  カレントディレクトリの変更("cd")
      "1"           ：  1列ファイル表示モードにする
      "2"           ：  2列ファイル表示モードにする
      "4"           ：  4列ファイル表示モードにする
      "c"           ：  ファイル/ディレクトリのコピー (注)
      "C"           ：  ファイル/ディレクトリのコピー (注)
                        (ディレクトリツリーによるコピー先指定)
      "d"           ：  ファイル/ディレクトリの削除
      "e"           ：  エディタの起動 ("em":Micro Emacs)
      "f"           ：  ファイル表示マスクの指定
      "j"           ：  ファイル名の先頭1文字を指定し、カーソルを移動する
      "q"           ：  ｆｕの終了
      "r"           ：  ファイルのリネーム(移動)
      "s"           ：  シェルコマンドの実行
      "t"           ：  ディレクトリツリーの表示と、カレントディレクトリの移動
      "T"           ：  カレントディレクトリを"/"とした、"t"コマンド
      "x"           ：  ファイルを実行コマンドとみなし実行
      "mo"          ：  "/dev/fd2d0a"を"/fd1"にマウント
      "um"          ：  "/dev/fd2d0a"のマウントの解除
      "md"          ：  ディレクトリの作成("mkdir")
      "al"          ：  アーカイブファイルの内容表示
      "ar"          ：  ファイルのアーカイブ実行
      "ua"          ：  アーカイブファイルからのファイルの取り出し
      "mv"          ：  ファイル/ディレクトリの移動 (注)
      "MV"          ：  ファイル/ディレクトリの移動 (注)
                        (ディレクトリツリーによる移動先指定)

    (注) "c","C","mv"または"MV"コマンドでファイルの複写/移動先に既にファイルが
         存在している場合どうするかを聞いてきます。ここで選択できる処理を以下
         に示します。
           's' : Skip そのファイルはコピー/移動しない
           't' : Time 変更日時を調べコピー/移動元の方が新しければコピー/移動する
           'f' : Force 強制的にコピー/移動する
           'a' : Abort コピー/移動は行なわずコマンドを抜ける
         これらを大文字で入力するとそれ以降のコピー/移動元に指定されている全て
         のファイルについてこの処理が適用されます。

  ５．２ ディレクトリ表示画面でのキー操作と機能
      SHIFT + 上    ：  １頁前のディレクトリ表示画面に移動
      SHIFT + 下    ：  １頁後のディレクトリ表示画面に移動
      前頁キー      ：  １頁前のファイル表示画面に移動
      次頁キー      ：  １頁後のファイル表示画面に移動
      リターンキー  ：  カーソルの示すディレクトリに移動
      ESC ESC       ：  ディレクトリ表示画面を抜ける
      スペースキー  ：  カーソル位置のディレクトリ検索
      Ctrl-N (or下) ：  カーソルを下に移動
      Ctrl-P (or上) ：  カーソルを上に移動
      Ctrl-F (or右) ：  カーソルを下に移動(カーソル位置が未検索ディレクトリ
                        の場合検索を行ないカーソル移動する)
      Ctrl-B (or左) ：  カーソルを上の階層のディレクトリに移動
      Ctrl-Z        ：  １頁前のファイル表示画面に移動
      Ctrl-V        ：  １頁後のファイル表示画面に移動
      "T"           ：  カーソル位置のディレクトリ検索
      "q"           ：  ディレクトリ表示画面を抜ける

  ５．３ 文字列入力時のキー操作と機能
      上矢印キー    ：  １つ前に入力された文字列の表示
      下矢印キー    ：  今表示されている次に入力された文字列の表示
      右矢印キー    ：  カーソルを右に移動
      左矢印キー    ：  カーソルを左に移動
      後退キー      ：  カーソル位置の１つ左の文字を削除
      削除キー      ：  カーソル位置の文字の削除
      ESC ESC       ：  文字列の入力の中断
      リターンキー  ：  文字列の確定
      文字キー      ：  入力された文字をカーソル位置に挿入

  ５．４ その他の場合のキー操作
      基本的にESC ESCまたは、"q"で操作、表示の中断を行います。

６．コマンドテンプレート
    'Shell','Exec'コマンドで入力された文字列やセットアップファイル中に記述
　されたコマンド文字列は'fu'によってマクロ文字を展開した後にシェルで実行し
　ています（以降これらの入力文字列及びセットアップファイル中のコマンド文字
　列をコマンドテンプレートと呼びます。）

          処      理                  例
      コマンドテンプレート          "em %*" (test.c test2.c test.hが選択
              ↓                             状態)
      マクロ文字を選択状態にある    "em test.c test2.c test.h"
      ファイル名に展開
              ↓
      シェルを起動し、コマンドを
      渡す。

  【コマンドテンプレートで使用できるマクロ文字】
      %f : 選択状態にあるファイルまたは、カーソル     "chmod u+x %f"
           位置のファイル名を順次置換し、実行する。          ↓
                                                      "chmod u+x test"
                                                      "chmod u+x test2"
                                                            .......

      %1 : カーソル位置にあるファイル名で置換し       "mv %1 test2"
           実行する。                                        ↓
                                                      "mv test test2"

      %* : 選択状態にあるファイルまたは、カーソル     "em %*"
           位置にあるファイル名をできるだけ置き換え          ↓
           一気に実行する。                           "em test1.c test2.c ..."

      %l : 選択状態にあるファイルまたは、カーソル     "cpio -o <%l >pak"
           位置にあるファイル名のリストを一時ファイル        ↓
           に格納し、そのファイル名で置き換える。　　 "cpio -o <.tempfile >pak"
                                                                   ↑
 　                                                 ファイル名リストファイル
  【マクロ文字の修飾子】
    マクロ文字には以下に示す4種類の修飾子を付けることができます。
    (例は全てカーソル位置のファイル名が"/usr/tashiro/aaa.bbb.c"であると仮定)
      @p : ファイル名のプレフィックス (例: "%1@p" -> "aaa.bbb")
      @s : ファイル名のサフィックス   (例: "%*@s" -> ".c")
      @d : カレントディレクトリパス   (例: "%1@d" -> "/usr/tashiro")
      @a : ファイルのフルパス名       (例: "%1@d" -> "/usr/tashiro/aaa.bbb.c")

７．ｆｕのカスタマイズ
　７．１ セットアップファイルによるカスタマイズ
    ５．で示したキーアサインはデフォルトの状態であり、セットアップファイルを
　作成する事で、キーアサインの変更、機能の追加を簡単に行う事ができます。
　  セットアップファイルは'/usr/lib'または各ユーザのホームディレクトリに
  '.setup.fu'の名前で作成して下さい（どちらにもあるとホームディレクトリにあ
　るものが有効になります。）
　　　注：セットアップファイルは'fu'立ち上げ時にのみ読み込まれます。
  　以下にはセットアップファイルのフォーマットを示します。

  (1) '#'で始まる行はコメントとみなします。
  (2) '#com'で始まる行は、コマンドメニュー部（画面下部）に表示する文字列の
　　　指定を行ないます。(複数行に分割可能)
      例: #com "Copy" "Delete" "Edit" "Find" "MaKe" "PRint" "Quit" "Shell"
          #com "Tree" "searchTree" "View" "eXecute"
  (3) その他の場合
      "keyname  switch  com_temp"
              ↑      ↑
            １個以上の空白またはTAB
        keyname  : コマンドをアサインするキーの指定
                    引用符'"'で囲まれている場合は、囲まれた文字列を、キー
　　　　　　　　　　コードとみなします。
                      特殊文字の記述方法
                         \000 : '\'に続く３桁の８進数をASCIIコードとみなし変換
                         \"   : '"'とみなす
                         \\   : '\'とみなす
                    それ以外の場合は、ｆｕで既に定義されているキーの名前とみ
　　　　　　　　　　なします。
　　　　　　　　　　例： "\033[A"    (esc),'[','A'
                         key_down    下矢印キー（2050でしか反応しないかも）
                         "del"       'd','e','l'
        switch   : コマンド実行時のモード指定（外部コマンドのみ有効）
                    1 : 'Shell>'モードになりコマンドテンプレートをユーザが修
                        正した後実行する。
                    0 : 'Shell>'モードにはならず即実行する。
        com_temp : アサインしたいコマンド
                    '$'で始まる場合には以降を内部コマンド名とみなします。
                    それ以外の場合にはコマンドテンプレートとみなします。
        （注） キー名リスト及び、コマンド名リストは、８．に記載します。

  【セットアップファイルの例】
      #
      #      File Utility Command Setup File
      #
      "e"         0     em %*
      "E"         1     em %*
      "pk"        1     cpio -p <%l >
      "up"        1     cat %1 | cpio -i
      "\016"      0     $func_down
      "\020"      0     $func_up
      "\030\003"  0     $func_quit
      key_zenpeji 0     $func_s_up
      key_jipeji  0     $func_s_down
　　（アーカイブされている'.setup.fu','.setup.fu.vi'は例です参考にして
      下さい）

　７．２ ヘッダファイルの変更によるカスタマイズ
　　以下に'fu'のヘッダファイルで定義されている定数や変数について説明します。
　これらを適当に修正し、リコンパイルすることでカスタマイズできます。
  【'fu.h'中の定数】
    #define FILE_ENT     1024    ファイル名を格納するエントリの数
    #define TREE_ENT     1024　　't'コマンド等で表示できるディレクトリ数
    #define USER_ID_ENT  1024　　ユーザIDとユーザ名の対応を格納するエントリ数
　　　　　　　　　　　　　　　　 （'/etc/passwd'のエントリより多くして下さい）
    #define GROUP_ID_ENT 256     グループIDの対応を格納するエントリ数
　　　　　　　　　　　　　　　　 （'/etc/group'のエントリより多くして下さい）
    #define MAX_KEY_FUNC 200　　 キーと機能の対応を登録するエントリ数
                                 （最低でも'.setup.fu'のエントリ+80は必要）
    #define MAX_FUNC_CMD 200　　 機能を登録するエントリ数
                                 （最低でも'.setup.fu'のエントリ+60は必要）
    #define HIST_CN      30　　　ヒストリバッファの行数
    #define LZHARC       "lha"   '*.lzh'ファイルに対するアーカイバを指定

  【'futable.h'中の変数】
    int sc_mode = 2;          起動時の画面表示モード
                                 1 : 1列ファイル表示モード
                                 2 : 2列ファイル表示モード
                                 4 : 4列ファイル表示モード
    int arc_mode = ARC_LZH;   デフォルトのアーカイバ
                                 ARC_LZH  : 'lha'            ('*.lzh')
                                 ARC_TAR  : 'tar'            ('*.tar')
                                 ARC_TAz  : 'tar'+'pack'     ('*.taz')
                                 ARC_TAZ  : 'tar'+'compress' ('*.taZ')
                                 ARC_TARz : 'tar'+'pack'     ('*.tar.z')
                                 ARC_TARZ : 'tar'+'compress' ('*.tar.Z')

８．ｆｕで登録しているキー名及び、コマンド名
  ８．１ キー名リスト(ほとんどが2050でのみ使用可)
    "key_torikesi"      :  取消
    "key_down"          :  ↓
    "key_up"            :  ↑
    "key_kakutyou"      :  機能拡張
    "key_pa1"           :  ＰＡ１
    "key_pa2"           :  ＰＡ２
    "key_pa3"           :  ＰＡ３
    "key_screen"        :  スクリーン
    "key_srq"           :  ＳＲＱ
    "key_pa4"           :  ＰＡ４
    "key_tyudan"        :  中断
    "ket_test"          :  テスト
    "key_jikkou"        :  実行
    "key_field"         :  フィールド
    "key_print"         :  印刷
    "key_henkantaishou" :  変換対象
    "key_function"      :  ファンクション
    "key_saihenkan"     :  再変換
    "key_s_function"    :  SHFT + ファンクション
    "key_data"          :  データ
    "key_stopprint"     :  印刷中止
    "key_c_function"    :  CTRL + ファンクション
    "key_s_home"        :  SHIFT + home
    "key_s_up"          :  SHIFT + ↑
    "key_s_down"        :  SHIFT + ↓
    "key_s_right"       :  SHIFT + →
    "key_s_left"        :  SHIFT + ←
    "key_s_bup"         :  SHIFT + [↑]
    "key_s_bdown"       :  SHIFT + [↓]
    "key_s_bright"      :  SHIFT + [→]
    "key_s_bleft"       :  SHIFT + [←]
    "key_s_zenpeji"     :  SHIFT + 前頁
    "key_s_jipeji"      :  SHIFT + 次頁
    "key_s_ins"         :  SHIFT + 挿入
    "key_s_del"         :  SHIFT + 削除
    "key_c_home"        :  CTRL + home
    "key_c_up"          :  CTRL + ↑
    "key_c_down"        :  CTRL + ↓
    "key_c_right"       :  CTRL + →
    "key_c_left"        :  CTRL + ←
    "key_c_bup"         :  CTRL + [↑]
    "key_c_bdown"       :  CTRL + [↓]
    "key_c_bright"      :  CTRL + [→]
    "key_c_bleft"       :  CTRL + [←]
    "key_c_zenpeji"     :  CTRL + 前頁
    "key_c_jipeji"      :  CTRL + 次頁
    "key_c_ins"         :  CTRL + 挿入
    "key_c_del"         :  CTRL + 削除
    "key_pf1"           :  ＰＦ１
    "key_pf2"           :  ＰＦ２
    "key_pf3"           :  ＰＦ３
    "key_pf4"           :  ＰＦ４
    "key_pf5"           :  ＰＦ５
    "key_pf6"           :  ＰＦ６
    "key_pf7"           :  ＰＦ７
    "key_pf8"           :  ＰＦ８
    "key_pf9"           :  ＰＦ９
    "key_pf10"          :  ＰＦ１０
    "key_pf11"          :  ＰＦ１１
    "key_pf12"          :  ＰＦ１２
    "key_c_pf1"         :  CTRL + ＰＦ１
    "key_c_pf2"         :  CTRL + ＰＦ２
    "key_c_pf3"         :  CTRL + ＰＦ３
    "key_c_pf4"         :  CTRL + ＰＦ４
    "key_c_pf5"         :  CTRL + ＰＦ５
    "key_c_pf6"         :  CTRL + ＰＦ６
    "key_c_pf7"         :  CTRL + ＰＦ７
    "key_c_pf8"         :  CTRL + ＰＦ８
    "key_c_pf9"         :  CTRL + ＰＦ９
    "key_c_pf10"        :  CTRL + ＰＦ１０
    "key_c_pf11"        :  CTRL + ＰＦ１１
    "key_c_pf12"        :  CTRL + ＰＦ１２
    "key_bleft"         :  [←]
    "key_bright"        :  [→]
    "key_ins"           :  挿入
    "key_del"           :  削除
    "key_bup"           :  [↑]
    "key_bdown"         :  [↓]
    "key_jipeji"        :  次頁
    "key_zenpeji"       :  前頁
    "key_right"         :  →
    "key_home"          :  home
    "key_left"          :  ←
    "key_dup"           :  DUP
    "key_fm"            :  FM
    "key_m_com1"        :  マウスでコマンドメニューの1番めをクリック
        ...                                  ...
    "key_m_com40"       :  マウスでコマンドメニューの40番めをクリック

  ８．２ コマンド名リスト
    "func_nop"          :  何もしない(キー設定解除の為のダミーコマンド)
    "func_mouse"        :  マウスの内部処理に使用(ユーザ使用不可)
    "func_ret"          :  ファイルの内容表示／ディレクトリの移動
    "func_select"       :  ファイルの選択
    "func_quit"         :  ｆｕを抜ける
    "func_delete"       :  ファイル/ディレクトリの削除
    "func_copy"         :  ファイル/ディレクトリのコピー
    "func_cp_tree"      :  ファイル/ディレクトリのコピー
                           (ツリー表示によってコピー先指定)
    "func_edit"         :  ファイルのエディト
    "func_exec"         :  ファイルを実行
    "func_shell"        :  シェルの起動
    "func_tree1"        :  ディレクトリのツリー構造表示
    "func_tree2"        :  ディレクトリのツリー構造を探索し、表示
    "func_find"         :  ファイル表示マスクの指定
    "func_up"           :  カーソルの上方向の移動
    "func_down"         :  カーソルの下方向の移動
    "func_left"         :  カーソルの左方向の移動
    "func_right"        :  カーソルの右方向の移動
    "func_s_up"         :  １頁前に移動
    "func_s_down"       :  １頁後に移動
    "func_bs"           :  バックスペースコマンド(文字列入力時)
    "func_del"          :  デリートコマンド(文字列入力時)
    "func_scr_1"        :  1列ファイル表示モードに
    "func_scr_2"        :  2列ファイル表示モードに
    "func_scr_4"        :  4列ファイル表示モードに
    "func_rdraw"        :  画面の再描画
    "func_all_sel"      :  表示されているファイル全部を選択状態にする
    "func_chdir"        :  カレントディレクトリの変更
    "func_rename"       :  ファイル名の変更(ファイルの移動)
    "func_mount"        :  フロッピーディスクのマウント(/dev/fd2d0a -> /fd1)
    "func_umount"       :  フロッピーディスクのアンマウント
    "func_mkdir"        :  ディレクトリの作成
    "func_arclist"      :  アーカイブファイルの内容表示
    "func_archive"      :  ファイルのアーカイブ
    "func_unarc"        :  ファイルのアンアーカイブ
    "func_pushd"        :  カレントディレクトリをスタックにプッシュ
    "func_popd"         :  スタックからディレクトリをポップ
    "func_jump"         :  ファイル名の先頭1文字を指定し、カーソルを移動 
    "func_move"         :  ファイル/ディレクトリの移動
    "func_mv_tree"      :  ファイル/ディレクトリの移動
                           (ツリー表示によってコピー先指定)
    "func_backdir"      :  一つ前のディレクトリに移動
    "func_forwdir"      :  一つ先のディレクトリに移動

９．利用制限等
  本プログラムはフリーウエアで著作権は放棄していません。なお配布、変更等に際
しては以下に示す注意事項を必ず守って下さい。

  (1) 著作権表示及び表示画面中の作者の名前を削除または変更しないで下さい。
  (2) 個人で使用する場合に限り自由に改変して構いません。
  (3) 再配布に際しては以下の事項を守って下さい。
    (a) 必ず無料で行なって下さい。(但し、郵送料等の実費は除きます)
    (b) 最低限サフィックスが'.doc'のファイルは添付してください。
    (c) バージョンアップにはできる限り対応して下さい。
    (d) できれば作者まで御一報下さい。(義務はありません)
  (4) 改変した本プログラムまたは、本プログラムの一部を使用したプログラムを公
      開する場合は以下の事項を守って下さい。
    (a) オリジナルとの差を明確にして下さい。
    (b) 事前に作者までご連絡下さい。
    (c) これらを使用して許可なく利益を得る行為は行なわないで下さい。
  (5) 本プログラムをパソコン通信以外のメディアで公開する場合は必ず作者の了解
      を得て下さい。
　(6) 本プログラムを使用したことによって生じた損害は保証いたしかねます。

１０．来  歴
  Ver 1.00  1990/04/16  T.Tashiro
    新規作成
  Ver 1.01  1990/04/17  T.Tashiro
    文字列入力及び、ディレクトリツリー表示時の削除動作を追加
  Ver 1.02  1990/04/17  T.Tashiro
    キー入力関数のバグをとる
  Ver 1.03  1990/04/18  T.Tashiro
    キー入力関数のバグをとる
  Ver 1.04  1990/04/20  T.Tashiro
    1文字入力ルーチンのバグフィックス
  Ver 1.05  1990/04/20  T.Tashiro
    ヒストリー機能のバグフィックス
  Ver 1.06  1990/05/14  T.Tashiro
    テキストファイルの表示部のバグをフィックス
  Ver 2.00  1990/07/23  T.Tashiro
    VT Terminalから使用可能に
    shellコマンドでcdが利くようになった
    shellコマンドを連続実行可能に
    ディレクトリツリー表示画面でpath位置を表示
    テキストファイルの表示がおかしかったのを修正
    ファイル検索時のマスク機能を追加
    copy時にディレクトリツリーが使用可に
    ファイル表示画面の分割数変更可に
  Ver 2.01  1990/07/27  T.Tashiro
    ファイル検索マスクとファイル名との比較関数のバグをフィックス
  Ver 2.02  1990/07/31  T.Tashiro
    ヒストリー機能を変更
  Ver 2.10  1990/08/08  T.Tashiro
    2050マウス対応バージョン
  Ver 2.11  1990/07/27  T.Tashiro
    ディレクトリツリーの検索許可/非許可機能を追加
  Ver 2.12  1990/09/12  T.Tashiro
    termcapエントリを使用するように変更した
  Ver 2.13  1990/10/15  T.Tashiro
    コマンドマクロの解析部のバグをフィックス
  Ver 2.14  1990/10/23  T.Tashiro
    コマンドメニューの最大値を20から40個に変更
  Ver 2.20  1991/01/25  T.Tashiro
    メインルーチンを変更
  Ver 2.30  1991/03/28  T.Tashiro
    プログラムの内部構造の変更
    アーカイバのサポート
    ディレクトリ単位のコピー/削除のサポート
  Ver 2.31  1991/03/28  T.Tashiro
    画面の行数の変化に対応するように変更
  Ver 2.32  1991/06/21  T.Tashiro
    ディレクトリスタック機能を追加
  Ver 2.33  1991/07/15  T.Tashiro
    14文字以上のファイル名に対応
  Ver 2.34  1991/07/16  T.Tashiro
    1文字検索のカーソルジャンプ機能
  Ver 2.35  1991/09/04  T.Tashiro
    外部コマンド実行後の端末設定の取り込みをやめた
  Ver 3.00  1991/11/26  T.Tashiro
    X Window System 対応オプションをつけた
    MINIX 対応のオプションをつけた
    半年以上前のファイルは時分の表示でなく年を表示するようにした
    Shellコマンドなどのヒストリバッファをファイルに退避するよう変更
    コマンドを実行する時,選択した順にファイル名を置き換えるよう変更
    ディレクトリをpushする際カーソル位置も覚えるように変更
    '~'や環境変数がcdコマンドやcopyコマンドで使用できるよう変更
    マクロを修飾するマクロオプションを使用可能にした
    シンボリックリンクされたファイルのコピーはリンクの張り直しに
    シンボリックリンクされたファイルの削除は本体とのアンリンクに変更
    copyコマンドでコピー先ファイルが既に存在するかを調べ、処理を問い合わせる
    様にした
    treeコマンドでサーチするのは最初カレントディレクトリのみにし、その後指定
    されたディレクトリのみサーチするように変更した
    (Ver3.00へのバージョンアップにあたり白井隆さん(GBA01426)に多大な協力を頂き、
     treeコマンドやシンボリックリンクへの対応などでソースコードを参考にさせて
     頂きました。ここに感謝致します。)
  Ver 3.01  1991/01/21  T.Tashiro
    "c"コマンド等での'~username'方式のディレクトリ指定でユーザ名が20字以上だと
    動作が不安定になるバグをフィックス（白井隆さんの指摘）
    "mv"および"MV"コマンドを追加
    MINIX ACK用に'search_tcp()'を'src_tcp()','search_cp()'を'src_cp()'に
    'strncat2()'を'strnct2()'に変更
    'fu.c'が大きくなりすぎたので'fu.c'と'kfunc.c'に分割した
　　空のディレクトリをコピー／削除しようとするとハングするバグを修正
    SunviewとOpenWindowsのShell-Toolでも'fu'が使用できるようにした
  Ver 3.02  1991/09/07  T.Tashiro
　　サフィックスが'.lzh'のファイルのデフォルトのアーカイバを'lha'に変更
　　アーカイブファイルの内容表示の出力をmore/pgでパイプする様に変更
　　xfuでシェルモード時には画面にその旨表示するよう変更
　　'%*'マクロでメモリの許す限りファイル名を置き換えるよう変更
　　EUC漢字コードに対応
　　xfuでカナのフォントファイルのコード範囲を自動認識するようにした
　　その他の細かいバグの修正
  Ver 3.03  1993/05/22  T.Tashiro
　　ディレクトリの削除でファイル名が14文字を越えるものがあると異常終了する
　　バグを修正
　　３行表示モードを追加
  Ver 3.04  1996/07/09  T.Tashiro
　　hpterm等のウインドウ枠の変形に追従する機能を追加
　　rootで実行した場合はタイトルの'='を'*'で表示
  Ver 3.05  1997/09/26  T.Tashiro
　　TABキーでファイル名を補完する機能を追加
　　'<','>'キーで一つ前のディレクトリに戻る/再度先に進む機能を追加
  Ver 3.06  1998/02/04  T.Tashiro
　　'-a'オプションを付けて起動するとcore dumpするバグを修正
  Ver 3.07  1998/06/18  T.Tashiro
　　３列表示モードの場合、長いファイル名があると１列の幅を調整して
　　ファイル名が全て表示されるようにした。

１１．バグその他
　現在'fu'には以下の不具合点が見つかっていますが修正されていません。
  (1) HP9000上の'hpterm'等で使用するとリバース表示部分が消える事があります。
  　　（機能的には問題ありません）
  (2) 'xfu'を2050以外の機種で使用すると強制終了される。特に、Sun上の
      OpenWindowsは相性が悪い。（'XMapRaized','XSetInputFocus'辺りがウイン
      ドウマネージャとけんかをする）

１２．その他
  プログラム名      ：  ＵｎｉｘＷＳ用ファイル管理ユーティリティ（ｆｕ）
  適用機種及びＯＳ  ：  HITACHI 2050ファミリー,HI-UX Rel3 以降
                        Sun SPARC Station SunOS
                        HP9000 Series HP-UX
                        MINIX Ver1.5 (PC-9801 ASCII-MINIX)
                        Linux on AT互換機
                        Sony NEWS 3400 NEWS-OS (Ver 3.91R)
                        Sony NEWS 3800 NEWS-OS (Ver 4.0.1R)
  プログラミング言語：  ＵＮＩＸ  Ｃ
  プログラム作成者  ：  田代 卓 (Nifty-ID PDC02432)
