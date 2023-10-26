package main

import (
	"fmt"

	"tump-cpp/setting"

	"github.com/TwilightUncle/ssgen"
)

func main() {
	env, _ := setting.GetEnv()
	baseUrl := "https://twilightuncle.github.io/tump-cpp"
	outputDir := "docs"
	if env == "local" {
		baseUrl = ""
		outputDir = "public"
	}

	err := ssgen.Default(
		baseUrl,
		"pages",
		"assets",
		"templates",
		outputDir,
	)
	if err != nil {
		fmt.Println(err)
		return
	}

	if err = ssgen.Build(); err != nil {
		fmt.Println(err)
		return
	}
}
