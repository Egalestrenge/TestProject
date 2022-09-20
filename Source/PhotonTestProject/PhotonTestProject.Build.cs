// Fill out your copyright notice in the Description page of Project Settings.

using System;
using System.IO;
using UnrealBuildTool;

public class PhotonTestProject : ModuleRules
{
	public PhotonTestProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		if(Target.Platform == UnrealTargetPlatform.Android)
        {
			var ManifestFile = Path.Combine(ModuleDirectory, "AndroidSanitizePermission_UPL.xml");
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", ManifestFile);
        }

        LoadPhoton(Target);
	}
	private string ModulePath
	{
		get { return ModuleDirectory; }
	}

	private string PhotonPath
	{
		get { return Path.GetFullPath(Path.Combine(ModulePath, "..", "Photon")); }
	}

	private string PlatformString
	{
		get { return Target.Platform == UnrealTargetPlatform.Win64 ? "x64" : "Win32"; }
	}

	private void AddPhotonLibPathWin(ReadOnlyTargetRules Target, string name)
	{
		#if UE_4_25_OR_LATER
			PublicAdditionalLibraries.Add(Path.Combine(PhotonPath, "lib", "Windows", name + "-cpp_vc16_release_windows_md_" + PlatformString + ".lib"));
		#else
			PublicAdditionalLibraries.Add(Path.Combine(PhotonPath, "lib", "Windows", name + "-cpp_vc15_release_windows_md_" + PlatformString + ".lib"));
		#endif
	}

	private void AddPhotonLibPathAndroid(ReadOnlyTargetRules Target, string name)
	{
	#if UE_5_0_OR_LATER
		PublicAdditionalLibraries.Add(Path.Combine(PhotonPath, "lib", "Android", "lib" + name + "_debug_android_arm64-v8a_libc++_no-rtti.a"));
	#else
		PublicAdditionalLibraries.Add(Path.Combine(PhotonPath, "lib", "Android", "lib" + name + "_debug_android_armeabi-v7a_no-rtti.a"));
	#endif
	}

	private void AddPhotonLibPathIOS(ReadOnlyTargetRules Target, string name)
	{
		string archStr = (Target.Architecture == "-simulator") ? "iphonesimulator" : "iphoneos";
		PublicAdditionalLibraries.Add(Path.Combine(PhotonPath, "lib", "iOS", "lib" + name + "_debug_" + archStr + ".a"));
	}

	private void AddPhotonLibPathMac(ReadOnlyTargetRules Target, string name)
	{
		PublicAdditionalLibraries.Add(Path.Combine(PhotonPath, "lib", "Mac", "lib" + name + "_debug_macosx.a"));
	}

	private void AddPhotonLibPathHTML5(ReadOnlyTargetRules Target, string name)
	{
		PublicAdditionalLibraries.Add(Path.Combine(PhotonPath, "lib", "HTML5", name + "-cpp_release_emscripten_Emscripten_unreal.bc"));
	}

	public bool LoadPhoton(ReadOnlyTargetRules Target)
	{
	#if UE_5_0_OR_LATER
		if (Target.Platform == UnrealTargetPlatform.Win64)
	#else
		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
	#endif
		{
			PublicDefinitions.Add("_EG_WINDOWS_PLATFORM");
			AddPhotonLibPathWin(Target, "Common");
			AddPhotonLibPathWin(Target, "Photon");
			AddPhotonLibPathWin(Target, "LoadBalancing");
		}
		else if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PublicDefinitions.Add("_EG_ANDROID_PLATFORM");
			AddPhotonLibPathAndroid(Target, "common-cpp-static");
			AddPhotonLibPathAndroid(Target, "photon-cpp-static");
			AddPhotonLibPathAndroid(Target, "loadbalancing-cpp-static");
			AddPhotonLibPathAndroid(Target, "websockets");
			AddPhotonLibPathAndroid(Target, "ssl");
			AddPhotonLibPathAndroid(Target, "crypto");
		}
		else if (Target.Platform == UnrealTargetPlatform.IOS)
		{
			PublicDefinitions.Add("_EG_IPHONE_PLATFORM");
			AddPhotonLibPathIOS(Target, "Common-cpp");
			AddPhotonLibPathIOS(Target, "Photon-cpp");
			AddPhotonLibPathIOS(Target, "LoadBalancing-cpp");
			AddPhotonLibPathIOS(Target, "ssl");
			AddPhotonLibPathIOS(Target, "crypto");
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicDefinitions.Add("_EG_IMAC_PLATFORM");
			AddPhotonLibPathMac(Target, "Common-cpp");
			AddPhotonLibPathMac(Target, "Photon-cpp");
			AddPhotonLibPathMac(Target, "LoadBalancing-cpp");
			AddPhotonLibPathMac(Target, "ssl");
			AddPhotonLibPathMac(Target, "crypto");
		}
	#if !UE_4_24_OR_LATER
		else if (Target.Platform == UnrealTargetPlatform.HTML5)
		{
			PublicDefinitions.Add("_EG_EMSCRIPTEN_PLATFORM");
			AddPhotonLibPathHTML5(Target, "Common");
			AddPhotonLibPathHTML5(Target, "Photon");
			AddPhotonLibPathHTML5(Target, "LoadBalancing");
		}
	#endif
		else
		{
			throw new Exception("\nTarget platform not supported: " + Target.Platform);
		}

		// Include path
		PublicIncludePaths.Add(Path.Combine(PhotonPath, "."));

		return true;
	}
}
