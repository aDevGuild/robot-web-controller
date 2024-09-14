import type { Hono } from 'hono';
import twilio from 'twilio';
import { openai } from '@ai-sdk/openai';
import { z } from 'zod';

import { env } from '../lib/env';
import { generateText } from 'ai';

const model = openai('gpt-4o-mini', { structuredOutputs: true });

export const createWebhookHandler = (router: Hono) => {
  router.post('/messages/reply', async (c) => {
    const twilioSignature = c.req.header('X-Twilio-Signature');
    if (
      !twilioSignature ||
      twilio.validateRequest(
        env.TWILIO_AUTH_TOKEN,
        twilioSignature,
        c.req.url,
        c.req.param(),
      )
    ) {
      return c.body(null, 403);
    }

    const formData = await c.req.formData();
    const [message] = z
      .tuple([z.string().trim()])
      .parse(formData.getAll('Body'));

    // TODO: save message history on database
    // const [phoneNumber] = z
    // 	.tuple([
    // 		z
    // 			.string()
    // 			.trim()
    // 			.transform((value) => value.split(':')[1]),
    // 	])
    // 	.parse(formData.getAll('From'));

    const { text } = await generateText({
      model,
      system: `
                Você é um agente robótico, especialista em micro-controladores e Machine Learning.
            `,
      prompt: `
                Responda a mensagem:
                ${message}
            `,
    });

    const messagingResponse = new twilio.twiml.MessagingResponse();
    messagingResponse.message(text);

    return c.text(messagingResponse.toString(), 200, {
      'Content-Type': 'text/xml',
    });
  });
};
