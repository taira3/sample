汎用解析ツール

ファイル毎の解析ツールを作成していると管理が煩雑になるので
起動部分を共通化したアプリとしてBonを開発する。

ファイル毎の解析ツールは、Pluginとして扱う。

■提供形式（構想中）

1.Default形式
　Bon(GUI)+Pluginフォルダの形式
　開発したPluginは、Pluginフォルダに置くことで利用可能。
　Bon.exe
　[Plugin]
　  Plugin1.dll
　  Plugin2.dll

2.CUIの形式
　Bon(CUI)+Pluginフォルダの形式
　開発したPluginは、Pluginフォルダに置くことで利用可能。
　Bon.exe
　[Plugin]
　  Plugin1.dll
　  Plugin2.dll
　
3.一体化(GUI)
　Bon(GUI)にPlugin内のDLLをStaticでリンクした形式。
　リンク済みのPluginのみ利用可能。Pluginの追加はビルドが必要。
　Bon.exe
　
4.一体化(CUI)
　Bon(CUI)にPlugin内のDLLをStaticでリンクした形式。
　リンク済みのPluginのみ利用可能。Pluginの追加はビルドが必要。
　Bon.exe

■内部構成

Bon内部構成として
・Plugin管理 (BonFW:Bon Framework)
・共通処理 (BonRT:Bon Runtime)
を核とし、GUIもしくはCUIから呼び出す。

PluginのDLLはBonFWで管理する。

Pluginは次のI/Fに対応する必要がある。
  Init()
  Info()
  Functions()
  Dispose()

Pluginは次のI/Fの対応については任意とする。
  [Pre/Post]Load( filename )
    ファイルの読み込み.
    
  [Pre/Post]Save( filename ) / Dump()
    ファイルの保存.
    解析情報の保存or表示
    
  [Pre/Post]Analyze( handle ) or Parse( handle )
    解析
    Bonからは、別スレッドで呼ばれる
    
  [Pre/Post]Verify( handle )
    妥当性確認.

  以下、お悩み中
   ?
  Command()
   ?
  [Pre/Post]Event
   ?
  [Pre/Post]Notify
  