﻿using System.Runtime.CompilerServices;

namespace Iron
{
    /// <summary>
    /// Component representing entity position, rotation and scale in the scene
    /// </summary>
    public class Transformation : Component
    {
        /// <summary>
        /// Global position
        /// </summary>
        public Vector3 Position
        {
            get => GetPosition_Internal(Entity.ID);
            set => SetPosition_Internal(Entity.ID, value);
        }
        
        /// <summary>
        /// Global rotation
        /// </summary>
        public Vector3 Rotation
        {
            get => GetRotation_Internal(Entity.ID);
            set => SetRotation_Internal(Entity.ID, value);
        }
        
        /// <summary>
        /// Global scale
        /// </summary>
        public Vector3 Scale
        {
            get => GetScale_Internal(Entity.ID);
            set => SetScale_Internal(Entity.ID, value);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Vector3 GetPosition_Internal(uint entityID);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetPosition_Internal(uint entityID, Vector3 position);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Vector3 GetRotation_Internal(uint entityID);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetRotation_Internal(uint entityID, Vector3 rotation);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Vector3 GetScale_Internal(uint entityID);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetScale_Internal(uint entityID, Vector3 scale);
    }
}