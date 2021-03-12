#include "AudioSystem.h"
#include "AudioCore.h"

void AudioSystem::OnComponentAdded(EntityID entityID, AudioSource& component)
{
    component.sourceID = AudioCore::CreateSource();
}

void AudioSystem::OnComponentRemoved(EntityID entityID, AudioSource& component)
{
    AudioCore::DeleteSource(component.sourceID);
}
