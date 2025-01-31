﻿namespace Iron
{
    /// <summary>
    /// Represents vector in 3D space
    /// </summary>
    public struct Vector3
    {
        /// <summary>
        /// X component
        /// </summary>
        public float X { get; }
        
        /// <summary>
        /// Y component
        /// </summary>
        public float Y { get; }
        
        /// <summary>
        /// Z component
        /// </summary>
        public float Z { get; }

        public Vector3(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public Vector3(float x, float y)
        {
            X = x;
            Y = y;
            Z = 0;
        }
        
        /// <summary>
        /// Vector with all components set to zero
        /// </summary>
        public static Vector3 Zero => new Vector3(0, 0, 0);
        
        /// <summary>
        /// Vector with all components set to 1
        /// </summary>
        public static Vector3 One => new Vector3(1, 1, 1);

        /// <summary>
        /// Return new vector with X component changed
        /// </summary>
        public Vector3 SetX(float x)
        {
            return new Vector3(x, Y, Z);
        }

        /// <summary>
        /// Return new vector with Y component changed
        /// </summary>
        public Vector3 SetY(float y)
        {
            return new Vector3(X, y, Z);
        }

        /// <summary>
        /// Return new vector with Z component changed
        /// </summary>
        public Vector3 SetZ(float z)
        {
            return new Vector3(X, Y, z);
        }
        
        public static Vector3 operator +(Vector3 a, Vector3 b) => new Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
        public static Vector3 operator -(Vector3 a, Vector3 b) => new Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
        public static Vector3 operator *(Vector3 a, float l) => new Vector3(a.X * l, a.Y * l, a.Z * l);
        public static Vector3 operator /(Vector3 a, float l) => new Vector3(a.X / l, a.Y / l, a.Z / l);
        public static Vector3 operator *(float l, Vector3 a) => new Vector3(a.X * l, a.Y * l, a.Z * l);
        
        public static bool operator ==(Vector3 a, Vector3 b) => Equals(a, b);
        public static bool operator !=(Vector3 a, Vector3 b) => !Equals(a, b);

        public override bool Equals(object obj)
        {
            if (obj is Vector3 vec)
                return Math.Approximately(X, vec.X) && Math.Approximately(Y, vec.Y) && Math.Approximately(Z, vec.Z);
            
            return base.Equals(obj);
        }
        
        public static implicit operator Vector3(Vector2 vector2)
        {
            return new Vector3(vector2.X, vector2.Y);
        }

        public override int GetHashCode()
        {
            unchecked
            {
                int result = 0;
                result = (result * 397) ^ X.GetHashCode();
                result = (result * 397) ^ Y.GetHashCode();
                result = (result * 397) ^ Z.GetHashCode();
                
                return result;
            }
        }

        public override string ToString()
        {
            return $"({X}; {Y}; {Z})";
        }
    }
}