// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

using UnrealBuildTool;
using System.Collections.Generic;

public class InfiniteDriverEditorTarget : TargetRules
{
	public InfiniteDriverEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "InfiniteDriver" } );
	}
}
