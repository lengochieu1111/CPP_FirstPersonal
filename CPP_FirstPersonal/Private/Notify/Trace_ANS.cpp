

#include "Notify/Trace_ANS.h"
#include "Interface/AttackInterface.h"

void UTrace_ANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp == nullptr) return;

	this->AttackInterface = TScriptInterface<IAttackInterface>(MeshComp->GetOwner());

	if (this->AttackInterface)
		this->AttackInterface->I_ANS_BeginTraceHit();

}

void UTrace_ANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	if (this->AttackInterface) 
		this->AttackInterface->I_ANS_TraceHit();
}
