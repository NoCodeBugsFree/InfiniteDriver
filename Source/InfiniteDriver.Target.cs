// Only 3dMotive and Crocopede has permission to redistribuite this project and all of its contents.

using UnrealBuildTool;
using System.Collections.Generic;

public class InfiniteDriverTarget : TargetRules
{
	public InfiniteDriverTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "InfiniteDriver" } );
	}
}
