﻿using System.Runtime.CompilerServices;

namespace Iron
{
    /// <summary>
    /// Components used to play <see cref="Animation"/>s
    /// </summary>
    public class Animator : Component
    {
        /// <summary>
        /// Sets new animation and plays it
        /// </summary>
        /// <param name="animation">Animation to play</param>
        public void Play(Animation animation)
        {
            PlayAnimation_Internal(Entity.ID, animation.ID);
        }
        
        /// <summary>
        /// Play or continue current animation
        /// </summary>
        public void Play()
        {
            Play_Internal(Entity.ID);
        }
        
        /// <summary>
        /// Pause animation
        /// </summary>
        public void Pause()
        {
            Pause_Internal(Entity.ID);
        }
        
        /// <summary>
        /// Stop playing animation
        /// </summary>
        public void Stop()
        {
            Stop_Internal(Entity.ID);
        }
        
        /// <summary>
        /// Play current animation from the start
        /// </summary>
        public void Restart()
        {
            Restart_Internal(Entity.ID);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void PlayAnimation_Internal(uint entityID, uint animationID);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Play_Internal(uint entityID);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Pause_Internal(uint entityID);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Stop_Internal(uint entityID);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Restart_Internal(uint entityID);
    }
}