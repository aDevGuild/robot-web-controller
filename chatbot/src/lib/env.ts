import { z } from 'zod';

export const env = z
  .object({
    PORT: z.number().default(8000),
    TWILIO_ACCOUNT: z.string(),
    TWILIO_AUTH_TOKEN: z.string(),
    OPENAI_API_KEY: z.string(),
  })
  .parse(process.env);
