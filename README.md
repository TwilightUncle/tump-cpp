# TumpCpp ドキュメント

下記の操作手順でHTMLを生成する。

1. GO言語をインストール
2. `go mod tidy`
3. jsおよび、cssはassets配下、画面の変更はpages配下のマークダウンを編集
4. `go run main.go`
5. githubへPUSH, docsディレクトリ配下をpagesで公開

## ローカルサーバー起動時のURL

- http://localhost:8080/

## env.jsonについて

- env: 値を指定しない場合デプロイ用のファイルを出力、localの場合、localサーバーで確認可能なように出力を行う
