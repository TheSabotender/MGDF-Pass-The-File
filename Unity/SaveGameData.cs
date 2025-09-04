using System;
using System.IO;
using UnityEngine;

[Serializable]
public class SaveGameData
{
    public static int integer_one;
    public static int integer_two;
    public static int integer_three;
    public static int integer_four;
    public static float float_one;
    public static float float_two;
    public static float float_three;
    public static Vector3 vector_one;
    public static Vector3 vector_two;

    [Serializable]
    private class SaveGameDataInternal
    {
        public int integer_one;
        public int integer_two;
        public int integer_three;
        public int integer_four;
        public float float_one;
        public float float_two;
        public float float_three;
        public Vector3 vector_one;
        public Vector3 vector_two;
    }

    public static string ToJson()
    {
        var data = new SaveGameDataInternal
        {
            integer_one = integer_one,
            integer_two = integer_two,
            integer_three = integer_three,
            integer_four = integer_four,
            float_one = float_one,
            float_two = float_two,
            float_three = float_three,
            vector_one = vector_one,
            vector_two = vector_two
        };
        return JsonUtility.ToJson(data);
    }

    public static void FromJson(string json)
    {
        var data = JsonUtility.FromJson<SaveGameDataInternal>(json);
        integer_one = data.integer_one;
        integer_two = data.integer_two;
        integer_three = data.integer_three;
        integer_four = data.integer_four;
        float_one = data.float_one;
        float_two = data.float_two;
        float_three = data.float_three;
        vector_one = data.vector_one;
        vector_two = data.vector_two;
    }

    public static string LoadStringFromFile(string path)
    {
        return File.ReadAllText(path);
    }

    public static void SaveToFile(string path)
    {
        File.WriteAllText(path, ToJson());
    }
}
