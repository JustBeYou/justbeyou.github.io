#include <iostream>
#include <string>

namespace NaiveDuplication
{
    class Rectangle
    {
    public:
        Rectangle(uint height, uint width) : height(height), width(width) {}

        void scale(uint numerator, uint denominator)
        {
            height = height * numerator / denominator;
            width = width * numerator / denominator;
        }

        std::string compute() const
        {
            std::string result("");
            for (uint i = 0; i < height; i++)
            {
                for (uint j = 0; j < width; j++)
                {
                    result += '*';
                }
                result += '\n';
            }
            return result;
        }

        std::string computeStrips() const
        {
            std::string result = this->compute();
            uint j = 0;
            for (uint i = 0; i < result.size(); i++)
            {
                if (result[i] != '*')
                {
                    continue;
                }

                if (++j % 2 == 0)
                {
                    result[i] = ' ';
                }
            }
            return result;
        }

        void draw(bool strips = false) const
        {
            std::string result;
            if (strips)
            {
                result = this->computeStrips();
            }
            else
            {
                result = this->compute();
            }
            std::cout << result << std::endl;
        }

    private:
        uint height, width;
    };

    class Waves
    {
    public:
        Waves(uint height, uint width) : height(height), width(width) {}

        void scale(uint numerator, uint denominator)
        {
            height = height * numerator / denominator;
            width = width * numerator / denominator;
        }

        std::string compute() const
        {
            std::string result("");
            for (uint i = 0; i < height; i++)
            {
                for (uint j = 0; j < width; j++)
                {
                    for (uint k = 0; k <= j; k++)
                    {
                        result += '*';
                    }
                    result += '\n';
                }
            }
            return result;
        }

        std::string computeStrips() const
        {
            std::string result = this->compute();
            uint j = 0;
            for (uint i = 0; i < result.size(); i++)
            {
                if (result[i] != '*')
                {
                    continue;
                }

                if (++j % 2 == 0)
                {
                    result[i] = ' ';
                }
            }
            return result;
        }

        void draw(bool strips = false) const
        {
            std::string result;
            if (strips)
            {
                result = this->computeStrips();
            }
            else
            {
                result = this->compute();
            }
            std::cout << result << std::endl;
        }

    private:
        uint height, width;
    };

    void test()
    {
        Rectangle r(4, 8);
        r.draw();
        r.draw(true);

        Waves w(2, 3);
        w.draw();
        w.draw(true);
    }
}

namespace Inheritance
{
    class Shape
    {
    public:
        Shape(uint height, uint width) : height(height), width(width) {}

        void scale(uint numerator, uint denominator)
        {
            height = height * numerator / denominator;
            width = width * numerator / denominator;
        }

        virtual std::string compute() const = 0;

        std::string computeStrips() const
        {
            std::string result = this->compute();
            uint j = 0;
            for (uint i = 0; i < result.size(); i++)
            {
                if (result[i] != '*')
                {
                    continue;
                }

                if (++j % 2 == 0)
                {
                    result[i] = ' ';
                }
            }
            return result;
        }

        void draw(bool strips = false) const
        {
            std::string result;
            if (strips)
            {
                result = this->computeStrips();
            }
            else
            {
                result = this->compute();
            }
            std::cout << result << std::endl;
        }

    protected:
        uint height, width;
    };

    class Rectangle : virtual public Shape
    {
    public:
        Rectangle(uint height, uint width) : Shape(height, width) {}

        std::string compute() const override
        {
            std::string result("");
            for (uint i = 0; i < height; i++)
            {
                for (uint j = 0; j < width; j++)
                {
                    result += '*';
                }
                result += '\n';
            }
            return result;
        }
    };

    class Waves : virtual public Shape
    {
    public:
        Waves(uint height, uint width) : Shape(height, width) {}

        std::string compute() const override
        {
            std::string result("");
            for (uint i = 0; i < height; i++)
            {
                for (uint j = 0; j < width; j++)
                {
                    for (uint k = 0; k <= j; k++)
                    {
                        result += '*';
                    }
                    result += '\n';
                }
            }
            return result;
        }
    };

    class HallowTriangle : virtual public Shape
    {
    public:
        HallowTriangle(uint height, uint width) : Shape(height, 0) {}

        std::string compute() const override
        {
            std::string result("");
            for (uint i = 0; i < height; i++)
            {
                for (uint j = 0; j <= i; j++)
                {
                    if (i == 0 || i == height - 1 || j == 0 || j == i)
                        result += '*';
                    else
                        result += ' ';
                }
                result += '\n';
            }
            return result;
        }
    };

    // override is ambiguous. diamon problem :P
    // class RectangleWaves : virtual public Rectangle, virtual public Waves
    // {

    // };

    void
    test()
    {
        Shape *shapes[] = {new Rectangle(2, 3), new Waves(3, 3), new HallowTriangle(6, 3)};
        for (auto shape : shapes)
        {
            shape->draw();
        }
    }
}

namespace Composition
{
    class ComputableShape
    {
    public:
        virtual std::string compute() const = 0;
    };

    class ScalableShape
    {
    public:
        virtual void scale(uint numerator, uint denominator) = 0;
    };

    class Drawable
    {
    public:
        virtual void draw() const = 0;
    };

    class ShapeDrawer : public Drawable
    {
    public:
        ShapeDrawer(ComputableShape *shape) : shape(shape) {}

        void draw() const override
        {
            std::cout << shape->compute() << std::endl;
        }

        ComputableShape *getShape() const
        {
            return this->shape;
        }

    protected:
        ComputableShape *shape;
    };

    class Rectangle : public ScalableShape, public ComputableShape
    {
    public:
        Rectangle(uint height, uint width) : height(height), width(width) {}

        void scale(uint numerator, uint denominator) override
        {
            height = height * numerator / denominator;
            width = width * numerator / denominator;
        }

        std::string compute() const override
        {
            std::string result("");
            for (uint i = 0; i < height; i++)
            {
                for (uint j = 0; j < width; j++)
                {
                    result += '*';
                }
                result += '\n';
            }
            return result;
        }

    private:
        uint height, width;
    };

    class Waves : public ComputableShape, public ScalableShape
    {
    public:
        Waves(uint height, uint width) : height(height), width(width) {}

        void scale(uint numerator, uint denominator) override
        {
            height = height * numerator / denominator;
            width = width * numerator / denominator;
        }

        std::string compute() const override
        {
            std::string result("");
            for (uint i = 0; i < height; i++)
            {
                for (uint j = 0; j < width; j++)
                {
                    for (uint k = 0; k <= j; k++)
                    {
                        result += '*';
                    }
                    result += '\n';
                }
            }
            return result;
        }

    private:
        uint height, width;
    };
    void
    test()
    {
        Drawable *toDraw[] = {
            new ShapeDrawer(new Rectangle(2, 3)),
            new ShapeDrawer(new Waves(4, 3))};

        for (auto drawable : toDraw)
        {
            // partea asta cu dynamic_cast nu are neaparat sens, e
            // doar ilustrativa pentru cum functioneaza
            ShapeDrawer *drawer = dynamic_cast<ShapeDrawer *>(drawable);
            if (drawer != nullptr)
            {
                ScalableShape *scalable = dynamic_cast<ScalableShape *>(drawer->getShape());
                std::cout << scalable << std::endl;
                if (scalable != nullptr)
                {
                    scalable->scale(2, 1);
                }
            }

            drawable->draw();
        }
    }
}

int main()
{
    NaiveDuplication::test();
    Inheritance::test();
    Composition::test();
    return 0;
}